var _TREE_ITEM_ID_CURRENT = 0;

/* ENUM: Selection Flags */
var SF_NONE = 0;
var SF_CURRENT = 1;

function XTreeItem(icon, text, data) {
    function allocateId() {
        return (_TREE_ITEM_ID_CURRENT++);
    };
    this.id = allocateId();
    this.parentNode = null;
    this.childNodes = [];
    this.expanded = false;
    this.selectionFlag = SF_NONE;
    this.displayIcon = icon;
    this.displayText = text;
    this.data = data;
}

XTreeItem.prototype = {
    constructor: XTreeItem,
    _getItemFromModel: function() {
        var item = this, paths = [];
        while (item) {
            paths.splice(0, 0, item.id);
            item = item.parentNode;
        }
        var model = listmodel;
        for (var i = 0; i < paths.length; ++i) {
            var bFound = false;
            for (var j = 0; j < model.count; ++j) {
                var node = model.get(j);
                if (paths[i] === node.id) {
                    if (i == paths.length - 1) {
                        return node;
                    } else {
                        model = node.childNodes;
                        bFound = true;
                        break;
                    }
                }
            }
            if (!bFound) {
                return null;
            }
        }
    },
    getLevel: function() {
        var level = 0, item = this;
        while (item.parentNode) {
            item = item.parentNode;
            ++level;
        }
        return level;
    },
    appendChild: function(item) {
        if (item.parentNode) {
            item.parentNode.removeChild(item);
        }
        item.parentNode = this;
        this.childNodes.push(item);
        var node = this._getItemFromModel();
        if (node) {
            node.childNodes.append(item);
        }
    },
    insertChild: function(pos, item) {
        if (item.parentNode) {
            item.parentNode.removeChild(item);
        }
        item.parentNode = this;
        this.childNodes.splice(pos, 0, item);
        var node = this._getItemFromModel();
        if (node) {
            node.childNodes.insert(pos, item);
        }
    },
    removeChild: function(item) {
        var i = this.childNodes.indexOf(item);
        this.childNodes.splice(i, 1);
        item.parentNode = null;
        var currentSelectionFlag = item.selectionFlag;
        item.setSelectionFlag(SF_NONE);
        if (currentSelectionFlag === SF_CURRENT) {
            if (this.childNodes.length > 0) {
                var nextCurrent = i;
                if (nextCurrent >= this.childNodes.length) {
                    nextCurrent = this.childNodes.length - 1;
                }
                this.childNodes[nextCurrent].setSelectionFlag(SF_CURRENT);
            } else {
                if (this.id !== self.mRootItem.id) {
                    this.setSelectionFlag(SF_CURRENT);
                }
            }
        }
        var node = this._getItemFromModel();
        if (node) {
            node.childNodes.remove(i);
        }
    },
    childItemAt: function(index) {
        return this.childNodes[index];
    },
    indexOfChildItem: function(item) {
        for (var i = 0; i < this.childNodes.length; ++i) {
            if (this.childNodes[i].id === item.id) {
                return i;
            }
        }
        return -1;
    },
    childrenCount: function(recursive) {
        if (!recursive) {
            recursive = false;
        }
        var count = this.childNodes.length;
        if (recursive) {
            for (var i = 0; i < this.childNodes.length; ++i) {
                count += this.childNodes[i].childrenCount(recursive);
            }
        }
        return count;
    },
    setExpanded: function(expanded) {
        this.expanded = expanded;
        var node = this._getItemFromModel();
        if (node) {
            node.expanded = expanded;
        }
    },
    setSelectionFlag: function(flag) {
        this.selectionFlag = flag;
        if (flag === SF_CURRENT) {
            self.mCurrentItem = this;
        } else {
            if (self.mCurrentItem.id === this.id) {
                self.mCurrentItem = null;
            }
        }
        var node = this._getItemFromModel();
        if (node) {
            node.selectionFlag = flag;
        }
    },
    setText: function(text) {
        this.displayText = text;
        var node = this._getItemFromModel();
        if (node) {
            node.displayText = text;
        }
    },
    setIcon: function(source) {
        this.displayIcon = source;
        var node = this._getItemFromModel();
        if (node) {
            node.displayIcon = source;
        }
    }
}
