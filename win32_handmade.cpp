#include <windows.h>

LRESULT
CALLBACK
MainWindowCallback(HWND window,
		   UINT message,
		   WPARAM w_param,
		   LPARAM l_param)
{
	LRESULT result = 0;
	PAINTSTRUCT paint = {};
	HDC device_context = {};
	int x_coordinate = 0;
	int y_coordinate = 0;
	int width = 0;
	int height = 0;
	static DWORD operation = BLACKNESS;

	switch(message) {
	case WM_SIZE:
		OutputDebugStringA("WM_SIZE\n");
		break;
	case WM_DESTROY:
		OutputDebugStringA("WM_DESTROY\n");
		break;
	case WM_CLOSE:
		OutputDebugStringA("WM_CLOSE\n");
		break;
	case WM_ACTIVATEAPP:
		OutputDebugStringA("WM_ACTIVATEAPP\n");
		break;
	case WM_PAINT:
		OutputDebugStringA("WM_PAINT\n");
		device_context = BeginPaint(window, &paint);
		x_coordinate = paint.rcPaint.left;
		y_coordinate = paint.rcPaint.top;
		width = paint.rcPaint.right - paint.rcPaint.left;
		height = paint.rcPaint.bottom - paint.rcPaint.top;

		PatBlt(device_context,
		       x_coordinate,
		       y_coordinate,
		       width,
		       height,
		       operation);

		switch(operation){
		case WHITENESS:
			operation = BLACKNESS;
			break;
		case BLACKNESS:
			operation = WHITENESS;
			break;
		}

		EndPaint(window, &paint);
		break;
	default:
		result = DefWindowProc(window, message, w_param, l_param);
	}

	return result;
}

int
CALLBACK
WinMain(HINSTANCE instance,
	HINSTANCE prev_instance,
	LPSTR command_line,
	int show_code)
{
	WNDCLASS window_class = {};
	unsigned short register_state = 0;
	HWND window_handle = {};
	MSG message = {};
	BOOL message_result = {};

	window_class.lpfnWndProc = MainWindowCallback;
	window_class.hInstance = instance;
	window_class.lpszClassName = "HandmadeHeroWindowClass";

	register_state = RegisterClassA(&window_class);

	if(!register_state){
		// Logging
	}

	window_handle =
		CreateWindowExA(0,
				window_class.lpszClassName,
				"Handmade Hero",
				WS_OVERLAPPEDWINDOW | WS_VISIBLE,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				0,
				0,
				instance,
				0);

	if(!window_handle){
		// Logging
	}

	for(;;) {
		message_result = GetMessageA(&message, 0, 0, 0);

		if(!message_result)
			break;

		TranslateMessage(&message);
		DispatchMessageA(&message);
	}

	return 0;
}
