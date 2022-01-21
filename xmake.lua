---@module xmake
---@field add_rules         function
---@field add_requires      function
---@field target            function
---@field set_kind          function
---@field add_cflags        function
---@field add_files         function
---@field add_headerfiles   function
---@field add_includedirs   function
---@field add_files         function
---@field add_packages      function
---@field target_end         function
---@field includes          function
---@field set_project       function
---@field set_version       function
---@field set_config        function

---@field require           function

set_project("UniGS")
set_version("1.0.0")
add_rules("mode.debug", "mode.release")

dependencies = {
     "protobuf-c"
};

add_requires(dependencies)
add_packages(dependencies)

add_cflags("-Wall", "-Wextra", "-Wpedantic", "-Werror", "-ggdb")

includes("library", "server", "testclient", "common")
