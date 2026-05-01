#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <cstdint>

    /* -- Lifecycle --------------------------------------------------------------- */

    /** Initialize the global Strata client. Call this once at startup. */
    void strataInit(const char *baseURL);

    /** Set the JWT access token (loaded from a previous session). */
    void strataSetToken(const char *token);

    /** Set the refresh token (loaded from a previous session). */
    void strataSetRefreshToken(const char *token);

    /**
     * Get the current access token.
     * Returns a newly-allocated C string — caller must free with strataFree().
     */
    char *strataGetToken(void);

    /**
     * Get the current refresh token.
     * Returns a newly-allocated C string — caller must free with strataFree().
     */
    char *strataGetRefreshToken(void);

    /** Free any string or buffer returned by a strata_* function. */
    void strataFree(char *ptr);

    /**
     * Get the last error message. Returns NULL if no error occurred.
     * The returned string must be freed with strataFree().
     */
    char *strataLastError(void);

    /* -- Health ------------------------------------------------------------------ */

    /**
     * GET /health
     * Returns: JSON {"status":"ok","service":"strata"} or NULL on error.
     */
    char *strataHealth(void);

    /* -- Auth -------------------------------------------------------------------- */

    /**
     * POST /api/v1/auth/register
     * Returns: JSON User object or NULL on error.
     */
    char *strataRegister(const char *username, const char *email, const char *password);

    /**
     * POST /api/v1/auth/login
     * Automatically stores the access + refresh tokens in the client.
     * Returns: JSON TokenPair or NULL on error.
     *
     * JSON shape:
     *   {"access_token":"...","refresh_token":"...","expires_in":3600}
     */
    char *strataLogin(const char *username, const char *password);

    /**
     * POST /api/v1/auth/refresh
     * Exchanges a refresh token for a new token pair and stores it.
     * Returns: JSON TokenPair or NULL on error.
     */
    char *strataRefresh(const char *refreshToken);

    /**
     * POST /api/v1/auth/logout
     * Clears stored tokens in the client.
     * Returns: JSON {"status":"logged out"} or NULL on error.
     */
    char *strataLogout(void);

    /* -- Projects ---------------------------------------------------------------- */

    /**
     * POST /api/v1/projects/
     * Returns: JSON Project or NULL on error.
     */
    char *strataProjectCreate(const char *name, const char *description);

    /**
     * GET /api/v1/projects/
     * Returns: JSON array of Project or NULL on error.
     */
    char *strataProjectList(void);

    /**
     * GET /api/v1/projects/{projectID}/
     * Returns: JSON Project or NULL on error.
     */
    char *strataProjectGet(const char *projectID);

    /**
     * DELETE /api/v1/projects/{projectID}/
     * Returns: JSON {"status":"deleted"} or NULL on error.
     */
    char *strataProjectDelete(const char *projectID);

    /* -- Push -------------------------------------------------------------------- */

    /**
     * POST /api/v1/projects/{projectID}/push/check
     * hashesJSON: JSON array string, e.g. '["abc123","def456"]'
     * Returns: JSON {"existing":[...],"needed":[...]} or NULL on error.
     */
    char *strataPushCheckChunks(const char *projectID, const char *hashesJSON);

    /**
     * POST /api/v1/projects/{projectID}/push/chunk
     * Uploads raw chunk bytes. hash is sent in the X-Chunk-Hash header.
     * Returns: 1 on success, 0 on error.
     */
    int strataPushUploadChunk(const char *projectID, const char *hash, const void *data, int dataLen);

    /**
     * POST /api/v1/projects/{projectID}/push/commit
     * bodyJSON: JSON-encoded CommitRequest:
     *   {
     *     "parent_commit_id": "..." | null,
     *     "message": "Initial commit",
     *     "ref": "main",
     *     "files": [
     *       {
     *         "path": "Content/Maps/Level01.umap",
     *         "total_size": 104857600,
     *         "chunk_hashes": ["hash1", "hash2", ...]
     *       }
     *     ]
     *   }
     * Returns: JSON CommitResult or NULL on error.
     *   {"commit_id":"...","ref":"main","files_updated":1,"total_new_chunks":42}
     */
    char *strataPushCommit(const char *projectID, const char *bodyJSON);

    /* -- Pull -------------------------------------------------------------------- */

    /**
     * POST /api/v1/projects/{projectID}/pull/diff
     * bodyJSON: JSON-encoded DiffRequest:
     *   {"from_commit_id": "..." | null, "to_commit_id": "..." }
     *   OR
     *   {"from_commit_id": "..." | null, "ref": "main"}
     * Returns: JSON diff result or NULL on error.
     */
    char *strataPullDiff(const char *projectID, const char *bodyJSON);

    /**
     * GET /api/v1/projects/{projectID}/pull/chunk/{hash}
     * Downloads a chunk's raw bytes.
     * outLen: set to the number of bytes returned.
     * Returns: pointer to raw bytes (free with strataFree()), or NULL on error.
     *
     * Example:
     *   int len = 0;
     *   void* data = strataPullDownloadChunk(projectID, hash, &len);
     *   if (data) {
     *     fwrite(data, 1, len, fp);
     *     strataFree((char*)data);
     *   }
     */
    void *strataPullDownloadChunk(const char *projectID, const char *hash, int *outLen);

    /* -- Version / Refs ---------------------------------------------------------- */

    /**
     * GET /api/v1/projects/{projectID}/refs
     * Returns: JSON array of Ref or NULL on error.
     */
    char *strataListRefs(const char *projectID);

    /**
     * GET /api/v1/projects/{projectID}/commits?limit=N&offset=N
     * Returns: JSON array of Commit or NULL on error.
     */
    char *strataListCommits(const char *projectID, int limit, int offset);

    /**
     * GET /api/v1/projects/{projectID}/commits/{commitID}
     * Returns: JSON Commit or NULL on error.
     */
    char *strataGetCommit(const char *projectID, const char *commitID);

    /**
     * GET /api/v1/projects/{projectID}/commits/{commitID}/files
     * Returns: JSON array of commit files or NULL on error.
     */
    char *strataListCommitFiles(const char *projectID, const char *commitID);

    /**
     * GET /api/v1/projects/{projectID}/tree?ref={ref}
     * Returns: JSON {"ref":"main","commit_id":"...","files":[...]} or NULL on error.
     */
    char *strataGetTree(const char *projectID, const char *ref);

    /* -- Branches / Merge -------------------------------------------------------- */

    /**
     * POST /api/v1/projects/{projectID}/branches
     * Returns: JSON Ref or NULL on error.
     */
    char *strataCreateBranch(const char *projectID, const char *name, const char *fromRef);

    /**
     * POST /api/v1/projects/{projectID}/merge/analyze
     * Returns: JSON MergeAnalysis or NULL on error.
     *   {"type":"fast_forward"|"clean"|"conflict","merge_base_id":"...",
     *    "source_branch":"...","target_branch":"...","conflicts":[...],...}
     */
    char *strataMergeAnalyze(const char *projectID, const char *sourceBranch, const char *targetBranch);

    /**
     * POST /api/v1/projects/{projectID}/merge
     * bodyJSON: JSON-encoded MergeExecuteRequest:
     *   {
     *     "source_branch": "feature/xyz",
     *     "target_branch": "main",
     *     "message": "Merge feature/xyz into main",
     *     "resolutions": [
     *       {"file_id": "...", "file_version_id": "..."}
     *     ]
     *   }
     * Returns: JSON {"commit":{...},"message":"Merge successful"} or NULL on error.
     */
    char *strataMergeExecute(const char *projectID, const char *bodyJSON);

    /* -- Locks ------------------------------------------------------------------- */

    /**
     * GET /api/v1/projects/{projectID}/locks/
     * Returns: JSON array of Lock or NULL on error.
     */
    char *strataLockList(const char *projectID);

    /**
     * POST /api/v1/projects/{projectID}/locks/
     * Returns: JSON Lock or NULL on error.
     */
    char *strataLockAcquire(const char *projectID, const char *filePath, const char *branch);

    /**
     * DELETE /api/v1/projects/{projectID}/locks/
     * force: 1 to force-release a lock owned by another user.
     * Returns: JSON {"status":"unlocked"} or NULL on error.
     */
    char *strataLockRelease(const char *projectID, const char *filePath, int force);

#ifdef __cplusplus
} /* extern "C" */
#endif

/* -- C++ RAII wrapper --------------------------------------------- */
#ifdef __cplusplus

#include <stdexcept>
#include <string>
#include <vector>

namespace strata
{

    /**
     * StrataError is thrown by the C++ wrapper when a Strata API call fails.
     */
    class StrataError : public std::runtime_error
    {
    public:
        explicit StrataError(const std::string &msg) : std::runtime_error(msg) {}
    };

    /**
     * RAII helper for strata-allocated strings.
     * Automatically calls strataFree() on destruction.
     */
    class StrataStr
    {
    public:
        explicit StrataStr(char *ptr) : ptr_(ptr) {}
        ~StrataStr()
        {
            if (ptr_)
                strataFree(ptr_);
        }

        // Implicit conversion to std::string.
        operator std::string() const { return ptr_ ? std::string(ptr_) : std::string(); }

        // Raw access.
        const char *c_str() const { return ptr_; }
        bool ok() const { return ptr_ != nullptr; }

        // Prevent copy — ownership is exclusive.
        StrataStr(const StrataStr &) = delete;
        StrataStr &operator=(const StrataStr &) = delete;

    private:
        char *ptr_;
    };

    /**
     * checkResult wraps a raw char* return from the C API.
     * Throws StrataError if the pointer is null (check lastError).
     */
    inline std::string checkResult(char *raw)
    {
        if (!raw)
        {
            StrataStr err(strataLastError());
            throw StrataError(err.ok() ? std::string(err) : "unknown error");
        }
        StrataStr s(raw);
        return std::string(s);
    }

    /**
     * Client is a thin C++ class wrapping the C API for convenience.
     * It does NOT parse JSON — results are always std::string (raw JSON).
     * Use a JSON library (nlohmann/json, rapidjson, etc.) to deserialize.
     */
    class Client
    {
    public:
        explicit Client(const std::string &baseURL)
        {
            strataInit(baseURL.c_str());
        }

        void setToken(const std::string &token) { strataSetToken(token.c_str()); }
        void setRefreshToken(const std::string &token) { strataSetRefreshToken(token.c_str()); }
        std::string getToken() { return checkResult(strataGetToken()); }
        std::string getRefreshToken() { return checkResult(strataGetRefreshToken()); }

        // -- Auth --
        std::string health() { return checkResult(strataHealth()); }
        std::string login(const std::string &u, const std::string &p)
        {
            return checkResult(strataLogin(u.c_str(), p.c_str()));
        }
        std::string registerUser(const std::string &u, const std::string &e, const std::string &p)
        {
            return checkResult(strataRegister(u.c_str(), e.c_str(), p.c_str()));
        }
        std::string refresh(const std::string &refreshToken)
        {
            return checkResult(strataRefresh(refreshToken.c_str()));
        }
        std::string logout() { return checkResult(strataLogout()); }

        // -- Projects --
        std::string projectCreate(const std::string &name, const std::string &desc = "")
        {
            return checkResult(strataProjectCreate(name.c_str(), desc.c_str()));
        }
        std::string projectList() { return checkResult(strataProjectList()); }
        std::string projectGet(const std::string &id) { return checkResult(strataProjectGet(id.c_str())); }
        std::string projectDelete(const std::string &id) { return checkResult(strataProjectDelete(id.c_str())); }

        // -- Push --
        std::string pushCheckChunks(const std::string &projectID, const std::string &hashesJSON)
        {
            return checkResult(strataPushCheckChunks(projectID.c_str(), hashesJSON.c_str()));
        }
        void pushUploadChunk(const std::string &projectID, const std::string &hash,
                             const void *data, int len)
        {
            if (!strataPushUploadChunk(projectID.c_str(), hash.c_str(), data, len))
            {
                StrataStr err(strataLastError());
                throw StrataError(err.ok() ? std::string(err) : "chunk upload failed");
            }
        }
        std::string pushCommit(const std::string &projectID, const std::string &bodyJSON)
        {
            return checkResult(strataPushCommit(projectID.c_str(), bodyJSON.c_str()));
        }

        // -- Pull --
        std::string pullDiff(const std::string &projectID, const std::string &bodyJSON)
        {
            return checkResult(strataPullDiff(projectID.c_str(), bodyJSON.c_str()));
        }
        std::vector<uint8_t> pullDownloadChunk(const std::string &projectID, const std::string &hash)
        {
            int len = 0;
            void *raw = strataPullDownloadChunk(projectID.c_str(), hash.c_str(), &len);
            if (!raw)
            {
                StrataStr err(strataLastError());
                throw StrataError(err.ok() ? std::string(err) : "chunk download failed");
            }
            auto *bytes = static_cast<uint8_t *>(raw);
            std::vector<uint8_t> result(bytes, bytes + len);
            strataFree(static_cast<char *>(raw));
            return result;
        }

        // -- Version / Refs --
        std::string listRefs(const std::string &projectID) { return checkResult(strataListRefs(projectID.c_str())); }
        std::string listCommits(const std::string &projectID, int limit = 50, int offset = 0)
        {
            return checkResult(strataListCommits(projectID.c_str(), limit, offset));
        }
        std::string getCommit(const std::string &projectID, const std::string &commitID)
        {
            return checkResult(strataGetCommit(projectID.c_str(), commitID.c_str()));
        }
        std::string listCommitFiles(const std::string &projectID, const std::string &commitID)
        {
            return checkResult(strataListCommitFiles(projectID.c_str(), commitID.c_str()));
        }
        std::string getTree(const std::string &projectID, const std::string &ref = "main")
        {
            return checkResult(strataGetTree(projectID.c_str(), ref.c_str()));
        }

        // -- Branches / Merge --
        std::string createBranch(const std::string &projectID, const std::string &name,
                                 const std::string &fromRef = "main")
        {
            return checkResult(strataCreateBranch(projectID.c_str(), name.c_str(), fromRef.c_str()));
        }
        std::string mergeAnalyze(const std::string &projectID,
                                 const std::string &src, const std::string &tgt)
        {
            return checkResult(strataMergeAnalyze(projectID.c_str(), src.c_str(), tgt.c_str()));
        }
        std::string mergeExecute(const std::string &projectID, const std::string &bodyJSON)
        {
            return checkResult(strataMergeExecute(projectID.c_str(), bodyJSON.c_str()));
        }

        // -- Locks --
        std::string lockList(const std::string &projectID) { return checkResult(strataLockList(projectID.c_str())); }
        std::string lockAcquire(const std::string &projectID, const std::string &path,
                                const std::string &branch = "main")
        {
            return checkResult(strataLockAcquire(projectID.c_str(), path.c_str(), branch.c_str()));
        }
        std::string lockRelease(const std::string &projectID, const std::string &path, bool force = false)
        {
            return checkResult(strataLockRelease(projectID.c_str(), path.c_str(), force ? 1 : 0));
        }
    };

} // namespace strata

#endif /* __cplusplus */
