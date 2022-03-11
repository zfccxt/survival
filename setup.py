import platform
import subprocess

if __name__ == "__main__":
    print("Running CMake...")
    if platform.system() == "Windows":
        subprocess.call("cmake -B build -G \"Visual Studio 16 2019\"")
    elif platform.system() == "Darwin":
        subprocess.call("cmake -B build -G Xcode", shell=True)
    print("CMake finished.")

