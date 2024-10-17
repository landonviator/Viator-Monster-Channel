[Setup]
AppName=Viator Monster Channel
AppVersion=1.0
DefaultDirName="C:\Program Files\Common Files\VST3\"
DefaultGroupName=Viator Plugins
OutputBaseFilename=viator-monster-channel-setup
Compression=lzma
SolidCompression=yes

[Files]
Source: "viator-monster-channel.zip"; DestDir: "C:\Program Files\Common Files\VST3\"; Flags: ignoreversion

[Icons]
Name: "{group}\Uninstall {cm:UninstallProgram,VST3 Plugin}"; Filename: "{uninstallexe}"

[Run]
Filename: "powershell.exe"; Parameters: "-NoProfile -ExecutionPolicy Bypass -Command ""Expand-Archive -LiteralPath 'C:\Program Files\Common Files\VST3\viator-monster-channel.zip' -DestinationPath 'C:\Program Files\Common Files\VST3\'"""; Flags: waituntilterminated runhidden
Filename: "cmd.exe"; Parameters: "/C del /Q ""C:\Program Files\Common Files\VST3\viator-monster-channel.zip"""; Flags: runhidden