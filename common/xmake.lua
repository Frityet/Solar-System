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
---@field add_defines       function



target("unigscommon")
do
    set_kind("static")
    add_files("src/**.c")
    add_headerfiles("src/**.h")
    add_includedirs("src", { public = true })
    add_includedirs("src/include")
    add_cflags("-Wall", "-Wextra", "-Wpedantic", "-Werror", "-ggdb")
    add_packages("lua")
    add_defines("UNIGS_DEBUG")
end
target_end()