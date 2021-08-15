This repository tests using pdfium as a static library.

## Building pdfium as a static library

It was nontrivial to build pdfium as a static library. Here is what I did

### Getting the Code

First, install `gclient`. This is easy. You just `git clone` the repo and add it
to your `PATH` environment variable.

Then, configure a `gclient` repo with `pdfium` in it (I don't really understand
what all this does and I'm not inclined to spend the time to learn about
`gclient` and what it is doing).

    mkdir pdfium_repo
    cd pdfium_repo
    gclient config --unmanaged https://pdfium.googlesource.com/pdfium.git
    gclient sync
    cd pdfium

When you install `gclient` you also get `gn` and `ninja`, which are used below.

### Generating build files

Run `gn args out/static` to bring up a text file that you can put your build
config in (the 'out/static' part can be any directory you want). Here is the
build conf that worked for me:

    is_debug = true
    pdf_is_standalone = true
    pdf_is_complete_lib = true
    is_component_build = false

    # I'm not sure if these need to be explicitly disabled or not
    clang_use_chrome_plugins = false
    use_xcode_clang = false
    use_custom_libcxx = false
    use_sysroot = false

    # Disable all the extra stuff I don't care about
    pdf_use_skia = false
    pdf_use_skia_paths = false
    pdf_enable_xfa = false
    pdf_enable_v8 = false
    use_goma = false

Then run `ninja -C out/static pdfium_all`, and the static library is in
`out/static/obj/libpdfium.a`. Put it in a directory called `libs` and run
the command in the Makefile to build the demo app

~
~
