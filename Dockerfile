FROM	debian:stable AS builder

# Install necessary utils and dependencies
RUN		apt-get update && apt-get install -y build-essential && apt-get clean

WORKDIR	/app

# Makefile buildsystem
COPY	. .

# Build strace
RUN		./configure.sh --debug --optimize-disable
RUN		make
RUN		make clean

# Final stage
FROM	debian:stable

# Copy binary
COPY	--from=builder /app/strace /usr/bin/strace

RUN		apt-get update && apt-get install -y procps && apt-get clean

RUN		chmod 755 /usr/bin/strace

RUN		useradd -m strace-user

RUN		echo 'Docker!' | passwd --stdin root 

USER	strace-user
