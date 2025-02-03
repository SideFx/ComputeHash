Small example on how to include a Go library into a (Qt6) C++ project:
![Screenshot 2025-01-21 141040](https://github.com/user-attachments/assets/af393953-9f72-49dc-b8f4-4cfe92fe8662)


Build static libsha512 library:
go build -buildmode=c-archive -o libsha512.a libsha512.go

