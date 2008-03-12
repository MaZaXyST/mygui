#ifndef __WIDGET_CONTAINER_H__
#define __WIDGET_CONTAINER_H__

#include "MyGUI.h"

typedef std::vector<std::pair<Ogre::String, Ogre::String> > StringPairs;
typedef std::map<Ogre::String, Ogre::String> MapString;

struct WidgetContainer
{
	WidgetContainer(){}
	WidgetContainer(std::string _type, std::string _skin, MyGUI::WidgetPtr _widget, std::string _name = ""):
		type(_type),
		skin(_skin),
		widget(_widget),
		name(_name),
		relative_mode(0)
	{}

	MyGUI::WidgetPtr widget;
	StringPairs mProperty;
	MapString mUserString;
	std::string type;
	std::string skin;
	//std::string position;
	//std::string position_real;
	//std::string layer;
	std::string align;
	Ogre::String name;
	// not for saving
	//inline type() { return widget->getWidgetType(); }
	inline std::string position(bool _percent = true)
	{
		if (relative_mode){
			std::string retval;
			char str[256];
			MyGUI::FloatCoord coord = MyGUI::Gui::getInstance().convertIntToRelative(widget->getCoord(), widget->getParent());
			if (_percent) sprintf(str, "%1.4g %1.4g %1.4g %.4g", coord.left*100, coord.top*100, coord.width*100, coord.height*100);
			else sprintf(str, "%3.9g %3.9g %3.9g %3.9g", coord.left, coord.top, coord.width, coord.height);
			retval = str;
			return retval;
		}
		return widget->getCoord().print();
	}
	inline std::string layer() { return widget->getLayerName(); }
	bool relative_mode;
};

class EditorWidgets{

	INSTANCE_HEADER(EditorWidgets);

public:
	void initialise();
	void shutdown();
	bool load(std::string _fileName);
	bool save(std::string _fileName);
	void loadxmlDocument(MyGUI::xml::xmlDocument * doc);
	MyGUI::xml::xmlDocument * savexmlDocument();
	WidgetContainer * find(MyGUI::WidgetPtr _widget);
	WidgetContainer * find(std::string _name);
	void add(WidgetContainer * _container);
	void remove(MyGUI::WidgetPtr _widget);
	void clear();

	std::vector<WidgetContainer*> widgets;
	int global_counter;
private:
	void parseWidget(MyGUI::xml::xmlNodeIterator & _widget, MyGUI::WidgetPtr _parent);
	void serialiseWidget(WidgetContainer * _container, MyGUI::xml::xmlNodePtr _node);
};

#endif // __WIDGET_CONTAINER_H__
