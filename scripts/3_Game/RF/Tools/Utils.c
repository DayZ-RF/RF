class RF_Utils<Class T>: Managed {

    static T If(bool condition, T result1, T result2) {
        if (condition) return result1;
        return result2;
    }
}

class RF_WUtils<Class T>: Managed {

    static T GetScript(Widget w) {
        T script;
        w.GetScript(script);
        return script;
    }
}