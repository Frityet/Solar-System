---@module xmake
---@field add_rules         function
---@field add_requires      function
---@field set_kind          function
---@field add_cflags        function
---@field add_ldflags       function
---@field add_files         function
---@field add_headerfiles   function
---@field add_includedirs   function
---@field add_files         function
---@field add_packages      function
---@field target            function
---@field target_end        function
---@field includes          function
---@field set_project       function
---@field set_version       function
---@field set_config        function
---@field add_defines       function
---@field toolchain         function
---@field set_sdkdir        function
---@field set_bindir        function
---@field set_toolset       function
---@field set_toolchains    function
---@field toolchain_end     function
---@field set_objectdir     function
---@field set_targetdir     function
---@field task              task
---@field task_end          function
---@field on_run            function
---@field import            function
---@field before_build      function
---@field package           function
---@field package_end       function
---@field set_url           function
---@field on_install        function
---@field git               git
---@field os                os
---@field after_link        function
---@field print             function
---@field set_languages     function

---@class git
---@field clone function
---@field pull function

---@class os
---@field isdir function
---@field execv function

---@class task
---@field run       function

set_project("SolarSystem")
set_version("0.1.0")
add_rules("mode.debug", "mode.release")

local DEPENDENCIES<const> = {
     "protobuf-c",
};

add_requires(DEPENDENCIES)

add_cflags("-Wall", "-Wextra", "-Wpedantic", "-Werror", "-ggdb", "-Og")
add_defines("SOLARSYSTEM_COMMON_DEBUG")

includes("spacestation", "satellite", "common", "test")
