# Interactive Web Shell Client v1.0

An interactive Python client for sending commands to web shells.  
This is a **prototype** intended for testing and learning purposes. Future updates will include enhanced security, authentication support, and improved response parsing.

> ⚠️ **Disclaimer:** Only use this tool on systems you own or have explicit permission to test. Unauthorised access to web shells is illegal.

## Features

- Interactive command-line shell interface
- Sends commands via **POST** (default) or **GET** requests
- Basic input sanitisation to filter control characters
- Strips HTML tags from server responses for easier reading
- Lightweight and easy to extend

## Usage:

```bash
python3 client.py <URL> <PARAM> [-X GET|POST]
```

- ```<URL>```: Target web shell URL (must include ```http://``` or ```https://```)
- ```<PARAM>```: Parameter name for sending commands
- ```-X GET|POST```: HTTP method (default: POST)

**Example**:

```bash
python3 client.py http://localhost:8080/shell.php cmd -X GET
python3 client.py http://localhost:8080/shell.php command
```

## Features to be Implemented

- Authentication support
- Command history persistence across sessions
- Improved output parsing

