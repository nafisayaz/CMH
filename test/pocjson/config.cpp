
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

/*  Walk up the directory tree until a directory containing <marker>
    is found.  Returns an empty path if the marker isn’t found.        */
fs::path find_root_by_marker(const fs::path& start, const std::string& marker = ".config")
{
    for (fs::path dir = fs::absolute(start); !dir.empty(); dir = dir.parent_path())
    {
        if (fs::exists(dir / marker) && fs::is_directory(dir / marker))
            return dir;                         // project root found
    }
    return {};                                  // marker not found
}

int main()
{
    fs::path cwd = fs::current_path();
    fs::path project_root = find_root_by_marker(cwd, ".config");

    if (project_root.empty())
    {
        std::cerr << "No .config directory found in any ancestor of "
                  << cwd << '\n';
        return 1;
    }

    // Source = <project_root>/.config
    fs::path source      = project_root / ".config";
    // Destination = <current working dir>/.config
    fs::path destination = cwd / ".config";

    try
    {
        fs::copy(source, destination, fs::copy_options::recursive);
        std::cout << "Copied " << source << " → " << destination << '\n';
    }
    catch (const fs::filesystem_error& e)
    {
        std::cerr << "Copy failed: " << e.what() << '\n';
        return 1;
    }
}
