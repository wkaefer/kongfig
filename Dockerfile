# Build and run kongfig in a consistent Ubuntu 22.04 environment.
#
# Build image:
#   docker build -t kongfig .
#
# Run the CLI:
#   docker run --rm -it kongfig
#
# Persistent config storage via $KONGFIG (mount a host directory):
#   docker run --rm -it \
#     -v "$HOME/.kongfig:/root/.kongfig" \
#     kongfig
#
# Override $KONGFIG to a custom path:
#   docker run --rm -it \
#     -e KONGFIG=/data/kongfig \
#     -v /host/path:/data/kongfig \
#     kongfig

FROM ubuntu:22.04

# Install build tools (gcc, make, ar, etc.)
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy all project sources into the image
COPY . .

# Add /app to PATH so that `kongfig` (shell script) and `kongfigtest`
# (compiled binary) are found by the Makefile test targets without needing ./
ENV PATH="/app:${PATH}"

# Build the project
RUN make

# Run the test suite at image build time — the build fails if tests fail
RUN make test

# Default command: run the kongfig shell-script CLI
CMD ["./kongfig"]
