FROM alpine
RUN apk add g++
COPY . .
RUN g++ main.cpp -masm=intel -o main
CMD ./main
