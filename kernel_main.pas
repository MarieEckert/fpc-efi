{$mode fpc}
unit kernel_main;

interface

procedure Print(fmt: PWideChar); cdecl; varargs; external 'c' name 'Print';

procedure kernel_start; cdecl;

implementation

procedure kernel_start; cdecl; [public, alias: 'kernel_start'];
begin
	Print('Test'#13#10);
end;

end.
