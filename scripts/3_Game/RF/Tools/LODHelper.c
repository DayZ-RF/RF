
class RF_LODHelper: Managed {

    static RF_LODSelectionData SpawnInternalEntityAI(string className, string selectionName, string lodName, Object parent) {
        if (!parent) return null;

        auto output = new RF_LODSelectionData();
        output.parent = parent;

        auto lod = parent.GetLODByName(lodName);
        if (!lod) return null;

        output.lod = lod;

        array<Selection> selections = {};
        lod.GetSelections(selections);

        foreach (auto selection : selections) {
            auto name = selection.GetName();
            if (name == selectionName) {
                if (selection.GetVertexCount() < 2) return null;

                output.selection = selection;

                output.firstPoint = GetVertexPoint(0, parent, lod, selection);
                output.secondPoint = GetVertexPoint(1, parent, lod, selection);
                output.thirdPoint = GetVertexPoint(2, parent, lod, selection);

                auto globalPosition = output.CurrentGlobalPosition();
                auto childObject = GetGame().CreateObject(className, globalPosition);
                if (!childObject) return null;

                auto child = EntityAI.Cast(childObject);
                if (!child) {
                    childObject.Delete();
                    return null;
                }

                vector mat[4];
                auto direction = output.CurrentGlobalDirection();
                auto directionUp = output.CurrentGlobalDirectionUp();
                mat[3] = output.CurrentGlobalPosition();
                Math3D.DirectionAndUpMatrix(direction, directionUp, mat);
                child.SetTransform(mat);

                output.child = child;

                return output;
            }
        }

        return null;
    }

    static vector GetVertexPoint(int vertexIndex, Object object, LOD lod, Selection selection) {
        auto lodVertexIndex = selection.GetLODVertexIndex(vertexIndex);
        return lod.GetVertexPosition(lodVertexIndex);
    }
}

class RF_LODSelectionData: Managed {

    // MARK: - Internal Properties

    Object parent;

    EntityAI child;

    LOD lod;

    Selection selection;

    vector firstPoint;

    vector secondPoint;

    vector thirdPoint;

    vector GetLocalPosition() {
        return firstPoint;
    }

    vector GetLocalDirection() {
        return vector.Direction(firstPoint, secondPoint);
    }

    vector GetLocalDirectionUp() {
        return vector.Direction(firstPoint, thirdPoint);
    }

    vector CurrentGlobalPosition() {
        return parent.ModelToWorld(firstPoint);
    }

    vector CurrentGlobalDirection() {
        auto firstGlobalPoint = parent.ModelToWorld(firstPoint);
        auto secondGlobalPoint = parent.ModelToWorld(secondPoint);
        return vector.Direction(firstGlobalPoint, secondGlobalPoint);
    }

    vector CurrentGlobalDirectionUp() {
        auto firstGlobalPoint = parent.ModelToWorld(firstPoint);
        auto thirdGlobalPoint = parent.ModelToWorld(thirdPoint);
        return vector.Direction(firstGlobalPoint, thirdGlobalPoint);
    }
}
