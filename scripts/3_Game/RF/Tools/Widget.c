class RF_Widget: Managed {
	
	static void RemoveChildrenFromWidget(Widget w) {
        while (w.GetChildren())
            w.RemoveChild(w.GetChildren());
    }
}