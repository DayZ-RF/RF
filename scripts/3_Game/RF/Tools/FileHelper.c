class RF_File: Managed {

    static TStringArray GetFilesList(string folder, string type = "json") {
        string fileName;
        int fileAttr, flags;
        bool found = true;
        TStringArray list = {};

        if (!FileExist(folder))
            MakeDirectory(folder);

        string path_find_pattern = folder + string.Format("/*.%1", type);
        FindFileHandle file_handler = FindFile(path_find_pattern, fileName, fileAttr, flags);

        while (found) {
            int pos = fileName.IndexOf(".");
            if (pos > -1)
                list.Insert(fileName.Substring(0, pos));
            found = FindNextFile(file_handler, fileName, fileAttr);
        }

        return list;
    }
}
