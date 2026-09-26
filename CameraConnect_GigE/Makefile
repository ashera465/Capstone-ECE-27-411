# --- Configuration ---
CXX = g++
TARGET = GigE_Conn.exe
APP_SRC = GigE_Conn.cpp

# Root directory where the primary meson.build resides
ARAVIS_ROOT = aravis-0.8.36/aravis-0.8.36

# Local path where we will output the compiled files
SDK_DIR = $(CURDIR)/aravis_sdk

# Let pkg-config resolve GLib natively from MSYS2
# We also include  local Aravis SDK directory explicitly
CXXFLAGS = -I$(SDK_DIR)/include/aravis-0.8 $(shell pkg-config --cflags glib-2.0 gobject-2.0)
LDFLAGS = -L$(SDK_DIR)/lib -laravis-0.8 $(shell pkg-config --libs glib-2.0 gobject-2.0)

# Default Goal
all: $(TARGET)

#Compile project using the locally built SDK files
$(TARGET): $(APP_SRC) $(SDK_DIR)/lib/libaravis-0.8.dll.a
	$(CXX) $(APP_SRC) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET)

#Compile the Aravis source folder into the local SDK folder
$(SDK_DIR)/lib/libaravis-0.8.dll.a:
	@echo "--- Compiling Aravis from your raw source folder ---"
	cd $(ARAVIS_ROOT) && meson setup src/build --prefix=$(SDK_DIR) --buildtype=release -Dviewer=disabled -Dintrospection=disabled -Dtests=false
	cd $(ARAVIS_ROOT) && meson compile -C src/build
	cd $(ARAVIS_ROOT) && meson install -C src/build

# Cleans compiled files
clean:
	del /Q $(TARGET)

# Use this if you want to wipe the build and re-compile Aravis from scratch
clean-sdk: clean
	rmdir /S /Q $(SDK_DIR)
	rmdir /S /Q $(ARAVIS_ROOT)\src\build

.PHONY: all clean clean-sdk
