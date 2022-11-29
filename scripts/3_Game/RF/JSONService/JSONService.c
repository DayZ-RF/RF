// JSON Helper
class JSONService<Class T>: Managed {

	// MARK: - Public

	// Read and convert filename to T
	//
	// - filename: File path
	// - data: T object
	static void ReadFile(string filename, out T data) {
		if (FileExist(filename)) {
			string file_content;
			string line_content;
			string error;
			FileHandle handle = OpenFile(filename, FileMode.READ);
			if (handle == 0) return;
			while (FGets(handle, line_content) >= 0) {
				file_content += line_content;
			}
			CloseFile(handle);
			JsonSerializer js = new JsonSerializer();
			if(!js.ReadFromString(data, file_content, error))
				Error(error);
		}
	}

	// Convert and write T object to file
	//
	// - filename: File path
	// - data: T object
	static void WriteFile(string filename, out T data) {
		string file_content;
		JsonSerializer js = new JsonSerializer();
		js.WriteToString(data, true, file_content);
		FileHandle handle = OpenFile(filename, FileMode.WRITE);
		if (handle == 0)
			return;
		FPrint(handle, file_content);
		CloseFile(handle);
	}

	// Convert string to T object
	//
	// - data: T object
	static T ReadString(string content) {
		T data;
		string error;
		JsonSerializer js = new JsonSerializer();
		js.ReadFromString(data, content, error);
		return data;
	}

	// Convert T object to string
	//
	// - data: T object
	static string WriteString(out T data) {
		string content;
		JsonSerializer js = new JsonSerializer();
		js.WriteToString(data, true, content);
		return content;
	}
}
