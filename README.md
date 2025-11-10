# HTTP Server

This project is an attempt to make a short HTTP server in plain C.

## Features

- [x] Server Connection Handling
- [ ] HTTP Parser
    - [x] Parse request line (method, URI, version)
	- [ ] Parse HTTP headers
	- [ ] Validate request format (struct)
- [ ] HTTP Responses
	- [x] **200 OK**
		- [ ] Send a minimal HTML page with correct response headers
	- [ ] **400 Bad Request**
	- [ ] **403 Forbidden**
	- [ ] **404 Not Found**
	- [ ] **500 Internal Server Error**
	- [ ] **501 Not Implemented**
- [ ] File Handling
	- [ ] Check if requested file exists
    - [ ] Serve HTML files
	- [ ] Serve binary files (images, PDFs, etc.)
	- [ ] Handle subdirectory requests
- [ ] Permissions and Security
	- [ ] Implement file access permissions
	- [ ] Verify paths to prevent directory traversal attacks (`../`)
	- [ ] Validate requested paths are within allowed directories
	- [ ] Sanitize file paths	
- [ ] Concurrency
	- [ ] Multi-threading support
	- [ ] Handle multiple simultaneous connections
	- [ ] Thread-safe resource access

Resources :

- [https://tools.ietf.org/html/rfc1945](https://tools.ietf.org/html/rfc1945)
- https://www.cs.columbia.edu/~danr/courses/6761/Fall00/hw/pa1/6761-sockhelp.pdf
