# Compiler und Flags
CC = gcc
CFLAGS = -Wall -fPIC

# Name der finalen Library
TARGET = RMT_FDM_DLL_FrameWork_FCS_RT.dll

# --- MODIFIZIERT ---
# Find all .c files, but exclude ert_main.c because it contains a `main`
# function which we don't want in a shared library.
SOURCES_ALL = $(wildcard *.c)
EXCLUDE_FILES = ert_main.c
SOURCES = $(filter-out $(EXCLUDE_FILES), $(SOURCES_ALL))

# Ersetze die .c Endung durch .o (für Objektdateien)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

# --- Build-Regeln ---

# Standardregel: Erstellt die Zieldatei
all: $(TARGET)

# Regel zum Linken der finalen Shared Library
$(TARGET): $(OBJECTS)
	$(CC) -shared -o $@ $^

# Regel zum Kompilieren einer einzelnen .c-Datei in eine .o-Datei
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Regel zum Aufräumen des Verzeichnisses
clean:
	@del $(OBJECTS) $(TARGET) 2>nul
