import QtQuick 2.0

RectangleBorders {
    width: 150
    height: parent.height
    signal toggleStatFilterSelection();

    ListView {
        id: listView
        interactive: false
        width: parent.width
        implicitHeight: contentHeight

        model: itemTypeFilterModel
        delegate: RectangleBorders {
            height: 30
            width: parent.width
            property bool filterActive: false
            rectColor: filterActive === true ? root.darkDarkGray : "#8c7400"

            Connections {
                target: equipment
                onFiltersUpdated: {
                    filterActive = equipment.getFilterActive(item_type)
                }
                onEquipmentSlotSelected: {
                    filterActive = equipment.getFilterActive(item_type)
                }
            }

            sendShiftClick: true
            sendCtrlClick: true
            onRectangleClicked: equipment.clearFiltersAndSelectSingle(item_type)
            onRectangleRightClicked: equipment.clearFiltersAndSelectSingle(item_type)
            onRectangleShiftClicked: equipment.selectRangeOfFiltersFromPrevious(item_type)
            onRectangleShiftRightClicked: equipment.selectRangeOfFiltersFromPrevious(item_type)
            onRectangleCtrlClicked: equipment.toggleSingleFilter(item_type)
            onRectangleCtrlRightClicked: equipment.toggleSingleFilter(item_type)

            Text {
                anchors.fill: parent
                text: desc

                font {
                    family: "Arial"
                    pointSize: 9
                }

                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    RectangleBorders {
        id: addStatFilterButton
        height: 30

        anchors {
            top: listView.bottom
            topMargin: 15
            left: parent.left
            right: parent.right
        }

        Text {
            text: "Add stat filter"

            font {
                family: "Arial"
                pointSize: 9
            }

            anchors.fill: parent

            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        onRectangleClicked: toggleStatFilterSelection()
        onRectangleRightClicked: activeStatFilterModel.clearFilters()
    }

    ListView {
        id: activeStatFilterView

        anchors {
            top:  addStatFilterButton.bottom
            topMargin: 15
            left: parent.left
            right: parent.right
        }

        interactive: false
        implicitHeight: contentHeight

        model: activeStatFilterModel
        delegate: EquipmentStatFilterBox {
            filterText: _description
            itemStatFlag: _itemstatflag
            comparator: _comparator
            compareValue: _comparevalue
        }
    }
}