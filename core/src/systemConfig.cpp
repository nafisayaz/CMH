#include "systemConfig.h"

bool CMH::SystemInit::initHome(){

    const char* home = std::getenv("HOME");
    if (!home) {
        std::cerr << "HOME environment variable not set.\n";
        return false;
    }
    std::filesystem::path gbsPath = std::filesystem::path(home) / ".gbs";

    if (! std::filesystem::exists(gbsPath)) {
        std::cerr << ".gbs does not exist.\n";
        return false;
    } 

    try {
        std::filesystem::path source = std::filesystem::absolute(gbsPath);
        std::filesystem::path destination = std::filesystem::current_path() / ".gbs";

        if (!std::filesystem::exists(source) || !std::filesystem::is_directory(source)) {
            std::cerr << "Source directory does not exist: " << source << '\n';
            return 1;
        }
        std::filesystem::copy(source, destination, std::filesystem::copy_options::recursive);
        std::cout << "Copied /.gbs to " << destination << '\n';

    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
        return false;
    }
    return true;

}


/*  Walk up the directory tree until a directory containing <marker>
    is found.  Returns an empty path if the marker isn’t found.        */
std::filesystem::path CMH::SystemInit::findRoot(const std::filesystem::path& start, const std::string& marker = ".gbs")
{
    for (std::filesystem::path dir = std::filesystem::absolute(start); !dir.empty(); dir = dir.parent_path())
    {
        if (std::filesystem::exists(dir / marker) && std::filesystem::is_directory(dir / marker))
            return dir;                         // project root found
    }
    return {};                                  // marker not found
}

bool CMH::SystemInit::init(){
    std::filesystem::path cwd = std::filesystem::current_path();
    std::filesystem::path project_root = findRoot(cwd, ".gbs");

    if (project_root.empty())
    {
        std::cerr << "No .gbs directory found in any ancestor of "
                  << cwd << '\n';
        return 1;
    }

    // Source = <project_root>/.gbs
    std::filesystem::path source      = project_root / ".gbs";
    // Destination = <current working dir>/.gbs
    std::filesystem::path destination = cwd / ".gbs";

    try
    {
        std::filesystem::copy(source, destination, std::filesystem::copy_options::recursive);
        std::cout << "Copied " << source << " → " << destination << '\n';
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "Copy failed: " << e.what() << '\n';
        return 1;
    }
}
