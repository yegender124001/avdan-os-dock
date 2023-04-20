pkgname="avdan-de-dock"
pkgver="0.0.2"
pkgrel="0"
pkgdesc="Dock like in Avdan OS"
arch=("x86_64")
depends=(
"qt5-base"
"qt5-quickcontrols2"
"qt5-quickcontrols"
"qt5-graphicaleffects"
"qt5-x11extras"
"kwindowsystem")
source=("AppItem.qml"
"applicationitem.h"
"applicationmodel.cpp"
"applicationmodel.h"
"CMakeLists.txt"
"DockItem.qml"
"Dock.qml"
"dockwindow.cpp"
"dockwindow.h"
"hamburgermenu.cpp"
"hamburgermenu.h"
"main.cpp"
"MainDock.qml"
"main.qml"
"NotificationDock.qml"
"processprovider.cpp"
"processprovider.h"
"qml.qrc"
"RightMenu.qml"
"systemappitem.cpp"
"systemappitem.h"
"systemappmonitor.cpp"
"systemappmonitor.h"
"SystemDock.qml"
"TaskBar.qml"
"tooltip.cpp"
"tooltip.h"
"Tooltip.qml"
"utils.cpp"
"utils.h"
"xwindowinterface.cpp"
"xwindowinterface.h")
sha512sums=(
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	"SKIP"
	)
build(){
	cmake -B build $srcdir -Wno-dev -DCMAKE_INSTALL_PREFIX='/usr'
	cmake --build build
}
package(){
	DESTDIR="$pkgdir" cmake --install build
}

