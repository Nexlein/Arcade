/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** DLLoader
*/

#include <dlfcn.h>

#include <iostream>
#include <memory>
#include <string>

#ifndef DLLOADER_HPP
#define DLLOADER_HPP

namespace arcade {

    /// @brief A class for loading and managing shared libraries
    /// @tparam T The type of the module to load
    template <typename T>
    class DLLoader {
        public:
        /// @brief Constructor that loads the shared library at the given filepath
        /// @param filepath The path to the shared library to load
        DLLoader(const std::string& filepath)
            : _handle(dlopen(filepath.c_str(), RTLD_LAZY), [](void* handle) {
                  if (handle) dlclose(handle);
              })
        {
            if (!_handle) std::cerr << "[DLLoader] " << dlerror() << std::endl;
        }

        /// @brief Get an instance of the loaded module
        /// @param entryPointName The name of the entry point function to call (default is
        /// "entryPoint")
        /// @return A pointer to the instance of the loaded module, or nullptr if there was an error
        T* getInstance(const std::string& entryPointName = "entryPoint")
        {
            if (!_handle) return nullptr;

            typedef T* (*EntryPointFunc)();

            EntryPointFunc createModule =
                (EntryPointFunc)dlsym(_handle.get(), entryPointName.c_str());

            if (createModule == nullptr) {
                std::cerr << "[DLLoader] dlsym Error: " << dlerror() << std::endl;
                return nullptr;
            }

            return createModule();
        }

        private:
        /// @brief A unique pointer that manages the handle to the loaded shared library, ensuring
        /// it is properly closed when the DLLoader is destroyed
        std::unique_ptr<void, void (*)(void*)> _handle;
    };
}  // namespace arcade

#endif /* !DLLOADER_HPP */
