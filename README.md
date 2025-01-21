Small example on how to include a Go library into a (Qt6) C++ project:
![image](https://github.com/user-attachments/assets/df9e68d3-6c46-467f-87b6-e575fd2f6cdc)

Build libsha512.go:
go build -buildmode=c-archive -o libsha512.a libsha512.go

