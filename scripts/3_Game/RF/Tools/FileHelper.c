class RF_File: Managed {

    // MARK: - Internal

    // DayZ 1.30 broke FindFile for "$profile:" patterns: every documented
    // FindFileFlags value returns no handle, while an out-of-range -1 still
    // enumerates (see https://report.bistudio.com/issues/DZEXP-134). The
    // documented flags go first, so once the engine is fixed nothing has to
    // change here. Backslashes are not found under 1.30 either, hence Replace.
    static FindFileHandle FindFileEx(string pattern, out string fileName, out FileAttr fileAttributes, int flags) {
        pattern.Replace("\\", "/");

        FindFileHandle handle = FindFile(pattern, fileName, fileAttributes, flags);
        if (handle) return handle;

        return FindFile(pattern, fileName, fileAttributes, -1);
    }

    static TStringArray GetFilesList(string folder, string type = "json") {
        string fileName;
        FileAttr fileAttr;
        TStringArray list = {};

        if (!FileExist(folder))
            MakeDirectory(folder);

        string path_find_pattern = folder + string.Format("/*.%1", type);
        FindFileHandle file_handler = FindFileEx(path_find_pattern, fileName, fileAttr, FindFileFlags.ALL);
        if (!file_handler)
            return list;

        bool found = true;
        while (found) {
            int pos = fileName.IndexOf(".");
            if (pos > -1)
                list.Insert(fileName.Substring(0, pos));
            found = FindNextFile(file_handler, fileName, fileAttr);
        }
        CloseFindFile(file_handler);

        return list;
    }
}
