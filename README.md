# CRAB

A basic top down scrolling game thing. Just playing with Allegro 4 and seeing what it can do across platforms.

![Crab Game Thing Screenshot](https://raw.githubusercontent.com/pcbits/crab/main/data/crab-screenshot.png)

# Allegro 4 and MappyAL dev tips

## Older GNU C Syntax
Fixed some syntax bugs in this code repos version of MappyAL. Also have to compile MappyAL and project with the older gnu standard of -std=gnu89. This can be seen in the makefile.dos.

Ex for DJGPP:
```
gcc -std=gnu89 main.c mappyal.c -c
gcc -std=gnu89 main.o mappyal.o -o main.exe -lalleg
```

## 8bit bitmaps and Windows

Create your images in 8bit/256 color mode then save them in 32bit/true/high color mode.
Windows has trouble opening true 8bit images in Allegro 4. This is a work around to allow all platforms to work.
See this form on hints to the topic: https://www.allegro.cc/forums/thread/616921

# Setting up Allegro 4 dev environments

How to setup allegro 4 for MSDOS, Windows, and Linux. Simple steps toward setting up cross compiler environments.

## A simple Allegro 4 program for testing.

You can uses this code below to test compiling.

```
#include <allegro.h>

int main()
{
    if (allegro_init()!=0) return 1;
    set_color_depth(32);
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0) !=0 )
        return 2;
    BITMAP* surface = create_bitmap(SCREEN_W, SCREEN_H);
    install_keyboard();
    clear_to_color(surface, makecol(255,255,255));
    circlefill(surface, 100, 100, 50, makecol(128,128,128));
    blit(surface, screen, 0,0,0,0,SCREEN_W,SCREEN_H);

    while (!keypressed())
        rest(20);

    allegro_exit();
    return 0;
}
END_OF_MAIN()
```

Resources:
https://www.programming4beginners.com/tutorial/allegro/a-short-allegro-program-for-testing

## Setting up DOSBOX-X, DJGPP and Allegro 4

1. Download and install DosBox-X

2. Get MSDOS disk images from archive.org or somewhere place them in the drivez folder reboot.

3. Create a Disk Image under "DOS" -> "Create blank disc image..." .

4. IMGMOUNT C <PATH_TO_IMG>

5. Then boot with the MSDOS images. `BOOT DISK1.IMG DISK2.IMG DISK3.IMG`

6. When it ask for next disk click "DOS" -> "Swap floppy drive"

7. Once install complete.

8. Next get DJGPP with Allegro lib from Zip Picker.

9. Copy files to a folder and MOUNT them follow install instructions for DJGPP.

10. After install to compile you use commands like so: `gcc main.c -o main.exe -lalleg`

Resources:
https://dosbox-x.com/wiki/Guide%3AInstalling-MS%E2%80%90DOS-6
https://www.delorie.com/djgpp/

## Setting up Windows and Allegro 4

1. Download allegro lib from: http://members.allegro.cc/EdgarReynaldo/BuildA4.html Direct Link: https://bitbucket.org/bugsquasher/unofficial-allegro-5-binaries/downloads/A443Deluxe.7z

2. Download MinGW-W64 file i686-posix-dwarf from: https://sourceforge.net/projects/mingw-w64/files/ Direct Link: https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/8.1.0/threads-posix/dwarf/i686-8.1.0-release-posix-dwarf-rt_v6-rev0.7z

3. Download Code::Blocks https://www.codeblocks.org/ . Download the setup file without mingw (currently codeblocks-20.03-setup.exe)

4. Extract archive MinGW-W64(i686-8.1.0-release-posix-dwarf-rt_v6-rev0.7z) and rename this folder to 'mingw' and move it to c:\

5. Extract archive Allegro(A443Deluxe.7z) and copy the bin lib and include folders from allegro to mingw:

```
COPY FILES IN DIRECTORY
FROM	->	TO

distro\include -> c:\mingw\include

distro\bin\dlls -> c:\mingw\bin (When it ask to replace files don't)
distro\bin\tools -> c:\mingw\bin
distro\bin\fonteditor -> c:\mingw\bin

distro\lib -> c:\mingw\lib
```

6. Install Code::Blocks

7. Setup code blocks.

	* First click "Settings" -> "Compiler..."

	* Click "Toolchain executables" tab and click "Auto-detect" if successful you should see a pop-up with "Auto-detected installation path of "GNU GCC Compiler" in "C:\mingw"" click OK.

	* Click "Search directories" tab

	* Under "Compiler" sub tab add "C:\mingw\include"

	* Under "Linker" sub tab add "C:\mingw\lib"

	* Under "Resource compiler" sub tab add "C:\mingw\bin"

	* Then click "Linker settings" tab add file "C:\mingw\lib\liballeg44.dll.a"

	* Then click "Compiler settings" tab select/check options of "Static libgcc", "Static libstdc++", "Static linking", and "Target x86 (32bit)" . !These options will give you a staticlly linked execute so you will not have to include almost all the dlls with your files and hopefully will let it run on older windows with 32bit only support!

	* Click OK on "Global compiler settings" dialog to close out.

	* From here Code Blocks is setup you can start a new Empty Project. Then click "Project" -> "Properties...".
	* Then click "Build targets" and under "Selected build target options" "Type:" select "GUI application" instead of "Console application".
	* Click OK to exit out of the dialog.

8. From here you can beging building an Allegro 4 application.

9. Compiling you just use the GUI build and run options.

Resources:
http://members.allegro.cc/EdgarReynaldo/BuildA4.html
https://sourceforge.net/projects/mingw-w64/files/

## Setting up Debian Linux with Allegro 4

You just install the dev package on Debian like so:
```
apt-get install liballegro4-dev
```
Then you compile like so:
```
gcc main.c -o main `allegro-config --libs`
```
You will have to incorp the allegro-config into your Makefiles etc...
Also if you are giving out binaries look into staticly compiling.
