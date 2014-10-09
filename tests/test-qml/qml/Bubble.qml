import QtQuick 2.0

Item {
    id: root
    visible: false
    function show(parent, text)
    {
        mainText.text = text;
        var co = mapFromItem(parent, root.x, root.y);

        var off = root.parent.width - (co.x + main.width);
        if( off < 0 )
        {
            root.x = co.x + off - 5;
            triangle.x = off * -1 + ( parent.width / 2 );
        }
        else
        {
            root.x = co.x - main.width / 2 + parent.width / 2;
            triangle.x = main.width / 2 - 5;
        }
        root.y = co.y - root.childrenRect.height - 5;
        root.visible = true;
    }

    function hide()
    {
        root.visible = false;
    }
    Rectangle {
        id: triangle
        anchors.top: main.bottom
        anchors.topMargin: -5
        width: 10
        height: 10
        color: "#d8d8d8"
        transform: Rotation { origin.x: 5; origin.y: 5; axis { x: 0; y: 0; z: 1 } angle: 45 }
    }
    Rectangle {
        id: main
        width: mainText.width + 10
        height: mainText.height + 10
        radius: 2
        color: "#d8d8d8"
        Text {
            id: mainText;
            anchors.centerIn: parent
        }
    }


}
