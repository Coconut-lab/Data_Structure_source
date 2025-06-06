#!/bin/bash

# 모든 소스 파일을 컴파일하여 실행 파일 생성
gcc -o calculator main.c iofun.c myfunc.c

# 실행 파일이 생성되었는지 확인 후 실행
if [ -f "./calculator" ]; then
    echo "컴파일 완료! 프로그램을 실행합니다."
    ./calculator
else
    echo "컴파일 오류가 발생했습니다."
fi
