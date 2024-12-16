# Variables
CXX = clang++
CXXFLAGS = -std=c++17 -I./include
TARGET = wct
SRC = src/wc_cli.cpp
BUILD_DIR = bin
INSTALL_DIR_LINUX = /usr/local/bin
INSTALL_DIR_TERMUX = /data/data/com.termux/files/usr/bin

# Detect environment
ifeq ($(shell uname -o), Android)
    INSTALL_DIR = $(INSTALL_DIR_TERMUX)
else
    INSTALL_DIR = $(INSTALL_DIR_LINUX)
endif

# Default target
all: $(BUILD_DIR)/$(TARGET)

# Build the binary
$(BUILD_DIR)/$(TARGET): $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(CXX) -o $(BUILD_DIR)/$(TARGET) $(SRC) $(CXXFLAGS)

# Install the binary to system path
install: all
	@mkdir -p $(INSTALL_DIR)
	cp $(BUILD_DIR)/$(TARGET) $(INSTALL_DIR)/
	@echo "Installed to $(INSTALL_DIR)."

# Uninstall the binary
uninstall:
	rm -f $(INSTALL_DIR)/$(TARGET)
	@echo "Uninstalled $(TARGET) from $(INSTALL_DIR)."

# Clean build files
clean:
	rm -rf $(BUILD_DIR)
