---@module xmake
---@field add_rules         function
---@field add_requires      function
---@field set_kind          function
---@field add_cflags        function
---@field add_files         function
---@field add_headerfiles   function
---@field add_includedirs   function
---@field add_files         function
---@field add_packages      function
---@field target            function
---@field target_end         function
---@field includes          function
---@field set_project       function
---@field set_version       function
---@field set_config        function

target("unigs-testclient")
do
    set_kind("binary")
    add_files("src/**.c")
    add_headerfiles("src/**.h")
    add_includedirs("src", "src/include")
    add_cflags("-Wall", "-Wextra", "-Wpedantic", "-Werror", "-ggdb")
end
target_end()
