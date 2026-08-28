// LJSON Helper: одна запись = одна компактная JSON-строка (line-delimited JSON).
// Для массивов записей (персистентность построек, логи и т.п.) — в отличие от
// JSONService не раздувает файл pretty-print'ом.
class LJSONService<Class T>: Managed {

    // MARK: - Private Static

    private static autoptr JsonSerializer js = new JsonSerializer();

    // MARK: - Public

    // Read file as array of T, one JSON document per line
    //
    // - filename: File path
    // - records: Output array (always allocated, empty if file missing/damaged)

    static void ReadFile(string filename, out array<ref T> records) {
        records = new array<ref T>();
        if (!FileExist(filename)) return;

        FileHandle handle = OpenFile(filename, FileMode.READ);
        if (handle == 0) return;

        if (!js) js = new JsonSerializer();

        string line;
        string error;
        while (FGets(handle, line) >= 0) {
            if (line.Length() < 2) continue;

            T record;
            if (!js.ReadFromString(record, line, error)) {
                Error(error);
                continue;
            }
            if (record) records.Insert(record);
        }
        CloseFile(handle);
    }

    // Write array of T to file, one compact JSON document per line
    //
    // - filename: File path
    // - records: Records to write

    static void WriteFile(string filename, array<ref T> records) {
        FileHandle handle = OpenFile(filename, FileMode.WRITE);
        if (handle == 0) return;

        if (!js) js = new JsonSerializer();

        foreach (T record : records) {
            string line;
            js.WriteToString(record, false, line);
            FPrintln(handle, line);
        }
        CloseFile(handle);
    }
}
