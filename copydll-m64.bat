@echo off
mkdir "%2\platforms\"
mkdir "%2\imageformats\"
copy "%1\..\plugins\imageformats\qico.dll" "%2\imageformats\"
copy "%1\..\plugins\platforms\qwindows.dll" "%2\platforms\"
copy "%1\Qt5Core.dll" "%2\"
copy "%1\Qt5Multimedia.dll" "%2\"
copy "%1\Qt5Svg.dll" "%2\"
copy "%1\Qt5PrintSupport.dll" "%2\"
copy "%1\Qt5Widgets.dll" "%2\"
copy "%1\Qt5Gui.dll" "%2\"
copy "%1\Qt5Network.dll" "%2\"
copy "%1\Qt5Xml.dll" "%2\"
copy "%1\icudt54.dll" "%2\"
copy "%1\icuin54.dll" "%2\"
copy "%1\icuuc54.dll" "%2\"

copy "%1\libstdc++-6.dll" "%2\"
copy "%1\libgcc_s_seh-1.dll" "%2\"
copy "%1\libwinpthread-1.dll" "%2\"
