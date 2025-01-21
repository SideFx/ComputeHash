@echo off
go build -buildmode=c-archive -o libsha512.a libsha512.go
