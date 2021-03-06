; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{748B660C-39E0-4D00-A611-9A14AE9E5704}
AppName=Dash
AppVersion=1.0
;AppVerName=Dash 1.0
AppPublisher=Cosine Gaming
AppPublisherURL=http://www.cosinegaming.com/
AppSupportURL=http://www.cosinegaming.com/
AppUpdatesURL=http://www.cosinegaming.com/
DefaultDirName={pf}\Dash
DefaultGroupName=Dash
AllowNoIcons=yes
OutputDir=C:\Users\Judah\Documents\GitHub\Dash\Release
OutputBaseFilename=DashSetup
SetupIconFile=C:\Users\Judah\Documents\GitHub\Dash\Dash.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\Users\Judah\Documents\GitHub\Dash\Release\Dash.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Judah\Documents\GitHub\Dash\Meshes\*"; DestDir: "{app}\Meshes"; Flags: ignoreversion
Source: "C:\Users\Judah\Documents\GitHub\Dash\Textures\*"; DestDir: "{app}\Textures"; Flags: ignoreversion 
Source: "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\lib\glut32.lib"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\Dash"; Filename: "{app}\Dash.exe"
Name: "{commondesktop}\Dash"; Filename: "{app}\Dash.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\Dash.exe"; Description: "{cm:LaunchProgram,Dash}"; Flags: nowait postinstall skipifsilent

