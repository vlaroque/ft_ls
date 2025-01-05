#!/bin/bash

# Create test directory and cd into it
TEST_DIR="ls_test_directory"
rm -rf "$TEST_DIR"
mkdir "$TEST_DIR"
cd "$TEST_DIR"

# Function to create files with specific dates
create_dated_file() {
    local filename="$1"
    local date="$2"
    touch "$filename"
    touch -t "$date" "$filename"
}

# Create directory structure
echo "Creating directory structure..."
mkdir -p deep/deeper/deepest
mkdir -p "dir with spaces/subdir"
mkdir -p .hidden_dir
mkdir -p empty_dir
mkdir -p "dir_with_very_long_name_that_exceeds_typical_terminal_width_to_test_formatting_and_wrapping_behavior_in_ls_output"

# Create various file types
echo "Creating different file types..."

# Regular files with different dates
create_dated_file "old_file" "202001010000"
create_dated_file "recent_file" "$(date +%Y%m%d0000)"
create_dated_file "future_file" "203001010000"

# Files with different permissions
touch "normal_file"
chmod 644 "normal_file"
touch "executable_file"
chmod 755 "executable_file"
touch "write_only_file"
chmod 222 "write_only_file"
touch "no_access_file"
chmod 000 "no_access_file"

# Files with special characters
touch "file with spaces"
touch "file_with_!@#\$%^&*()"
touch ".hidden_file"
touch "file.with.dots"
touch "file_ending_with_dot."
touch "file_ending_with_space "

# Files with different sizes
dd if=/dev/zero of=empty_file bs=1 count=0 2>/dev/null
dd if=/dev/zero of=small_file bs=1 count=1024 2>/dev/null
dd if=/dev/zero of=medium_file bs=1K count=1024 2>/dev/null
dd if=/dev/zero of=large_file bs=1M count=10 2>/dev/null

# Create symbolic links
echo "Creating symbolic links..."
ln -s "normal_file" "normal_symlink"
ln -s "nonexistent_file" "broken_symlink"
ln -s "../$TEST_DIR" "recursive_symlink"
ln -s "deep/deeper/deepest" "relative_symlink"
ln -s "/absolute/path/symlink" "absolute_symlink"
ln -s ".." "parent_dir_symlink"
ln -s "." "current_dir_symlink"

# Create hard links
echo "Creating hard links..."
touch "original_file"
ln "original_file" "hardlink1"
ln "original_file" "hardlink2"
ln "original_file" "hardlink3"

# Create special files (if running as root, otherwise skip)
if [ "$(id -u)" = "0" ]; then
    echo "Creating special files (requires root)..."
    mknod char_device c 1 3    # null device
    mknod block_device b 8 0   # first SCSI device
    mkfifo named_pipe
    
    # Set special permissions
    chmod 4755 "executable_file"  # setuid
    chmod 2755 "group_executable" # setgid
    chmod 1777 "sticky_dir"       # sticky bit
else
    echo "Skipping special files creation (requires root)"
fi

# Create files with different ownership (if possible)
if [ "$(id -u)" = "0" ]; then
    echo "Creating files with different ownership..."
    touch "root_owned_file"
    chown root:root "root_owned_file"
    touch "user_owned_file"
    chown 1000:1000 "user_owned_file"
fi

# Create nested structure with many files
echo "Creating nested structure..."
for i in {1..100}; do
    mkdir -p "deep/deeper/deepest/dir$i"
    touch "deep/deeper/deepest/dir$i/file$i"
done

# Create files to test sorting
echo "Creating files for sort testing..."
touch "1_numeric_first"
touch "a_alpha_first"
touch "Z_alpha_upper"
touch "z_alpha_lower"
touch "_underscore_first"
touch ".dot_first"

# Set timestamps for different time display formats
echo "Setting various timestamps..."
for month in {1..12}; do
    padded_month=$(printf "%02d" $month)
    create_dated_file "file_${padded_month}" "2023${padded_month}010000"
done

# Create various special cases
echo "Creating special cases..."
touch $'file_with\nnewline'
touch $'file_with\ttab'
touch $'file_with\\backslash'
touch $'file_with\'simplequote'
touch $'file_with"doublequote'
touch "file_ending_without_newline"

# Create files with ACLs if supported
if command -v setfacl &> /dev/null; then
    echo "Creating files with ACLs..."
    touch "file_with_acl"
    setfacl -m u:1000:rx "file_with_acl"
fi

# Create extended attributes if supported
if command -v setfattr &> /dev/null; then
    echo "Creating files with extended attributes..."
    touch "file_with_xattr"
    setfattr -n user.test -v "test_value" "file_with_xattr"
fi

echo "Test environment created in $TEST_DIR"
echo "Total files and directories created: $(find . -mindepth 1 | wc -l)"

# Print test cases for verification
echo "
Test cases created:
1. Files with different dates (old, recent, future)
2. Files with different permissions (644, 755, 222, 000)
3. Files with special characters (spaces, symbols, dots)
4. Files with different sizes (empty to 10MB)
5. Various symbolic links (normal, broken, recursive)
6. Hard links with multiple references
7. Special files (if root: char device, block device, named pipe)
8. Different ownership and groups (if root)
9. Deep directory structure with many files
10. Files for testing sort order
11. Files with special names (newlines, tabs)
12. Files with ACLs and extended attributes (if supported)
13. Hidden files and directories
14. Empty directories
15. Long filenames
16. Files with spaces and special characters
"
