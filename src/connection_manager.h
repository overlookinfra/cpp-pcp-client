#ifndef CTHUN_CLIENT_SRC_CONNECTION_MANAGER_H_
#define CTHUN_CLIENT_SRC_CONNECTION_MANAGER_H_

#include "client.h"
#include "endpoint.h"
#include "connection.h"

#include <vector>
#include <string>
#include <memory>

namespace Cthun {
namespace Client {

//
// CONNECTION_MANAGER singleton
//

#define CONNECTION_MANAGER ConnectionManager::Instance()

class ConnectionManager {
  public:
    // TODO(ale): function to reset the Endpoint

    static ConnectionManager& Instance();

    /// Throw...
    void configureSecureEndpoint(const std::string& ca_crt_path,
                                 const std::string& client_crt_path,
                                 const std::string& client_key_path);

    Connection::Ptr createConnection(std::string url);

    /// Throw...
    void open(Connection::Ptr connection_ptr);

    /// Throw...
    void send(Connection::Ptr connection_ptr, Message message);

    /// Throw...
    void close(Connection::Ptr connection_ptr,
               Close_Code code = Close_Code_Values::normal,
               Message reason = DEFAULT_CLOSE_REASON);

    /// Throw...
    void closeAllConnections();

    // TODO(ale): do we need a method to get all existent connections?

  private:
    Endpoint::Ptr endpoint_ptr_;
    bool is_secure_ { false };
    std::string ca_crt_path_;
    std::string client_crt_path_;
    std::string client_key_path_;

    // To control the lazy instantiation of the endpoint
    bool endpoint_running_;

    ConnectionManager();

    void startEndpointIfNeeded();
};

}  // namespace Client
}  // namespace Cthun

#endif  // CTHUN_CLIENT_SRC_CONNECTION_MANAGER_H_
