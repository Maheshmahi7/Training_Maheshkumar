#include "XMLDomReader.h"



/*parameterized constructor to assign the readed file to a local instance*/
XMLDomReader::XMLDomReader(DOMDocument* doc)
{	
	xmlDoc = doc;
}

XMLDomReader::~XMLDomReader()
{
}

/*method to get the text content from the node*/
string XMLDomReader::getChildValue(const char* parentTag, int parentIndex, const char* childTag, int childIndex)
{
	XMLCh* temp = XMLString::transcode(parentTag);
	DOMNodeList* list = xmlDoc->getElementsByTagName(temp);
	XMLString::release(&temp);

	DOMElement* parent = dynamic_cast<DOMElement*>(list->item(parentIndex));
	DOMElement* child =
		dynamic_cast<DOMElement*>(parent->getElementsByTagName(XMLString::transcode(childTag))->item(childIndex));
	string value;
	if (child) {
		char* temp2 = XMLString::transcode(child->getTextContent());
		value = temp2;
		XMLString::release(&temp2);
	}
	else {
		value = "";
	}
	return value;
}
/*method to get child element using attribute value*/
string XMLDomReader::getChildByAttribute(const char* parentTag, const char* childTag , const char* attributevalue){
	const char* attributeTag = "ID";
	int parentIndex = 0;
	const char* value;
	XMLCh* temp = XMLString::transcode(parentTag);
	DOMNodeList* list = xmlDoc->getElementsByTagName(temp);
	XMLString::release(&temp);
	while (true){
	DOMElement* parent = dynamic_cast<DOMElement*>(list->item(parentIndex));
	temp = XMLString::transcode(attributeTag);
	char* temp2 = XMLString::transcode(parent->getAttribute(temp));
	if (strcmp(attributevalue, temp2) == 0){
		DOMElement* child =
			dynamic_cast<DOMElement*>(parent->getElementsByTagName(XMLString::transcode(childTag))->item(0));
		if (child) {
			value = XMLString::transcode(child->getTextContent());
				break;
			}
			else{
				value = NULL;
			}
			XMLString::release(&temp2);
		}
		else {
			parentIndex++;
		}
	}
	return value;
}
/*method to get the child attribute value*/
string XMLDomReader::getChildAttribute(const char* parentTag, int parentIndex, const char* childTag, int childIndex)
{
	const char* attributeTag = "ID";
	XMLCh* temp = XMLString::transcode(parentTag);
	DOMNodeList* list = xmlDoc->getElementsByTagName(temp);
	XMLString::release(&temp);

	DOMElement* parent = dynamic_cast<DOMElement*>(list->item(parentIndex));
	DOMElement* child =
		dynamic_cast<DOMElement*>(parent->getElementsByTagName(XMLString::transcode(childTag))->item(childIndex));
	const char* value;
	if (child) {
		temp = XMLString::transcode(attributeTag);
		char* temp2 = XMLString::transcode(child->getAttribute(temp));
		value = temp2;
		XMLString::release(&temp2);
	}
	else {
		value = NULL;
	}
	return value;
}

/*method to get the number of root elements*/
int XMLDomReader::getRootElementCount(const char* rootElementTag)
{
	DOMNodeList* list = xmlDoc->getElementsByTagName(XMLString::transcode(rootElementTag));
	return (int)list->getLength();
}

/*method to get the number of child elements*/
int XMLDomReader::getChildCount(const char* parentTag, int parentIndex, const char* childTag)
{
	XMLCh* temp = XMLString::transcode(parentTag);
	DOMNodeList* list = xmlDoc->getElementsByTagName(temp);
	XMLString::release(&temp);

	DOMElement* parent = dynamic_cast<DOMElement*>(list->item(parentIndex));
	DOMNodeList* childList = parent->getElementsByTagName(XMLString::transcode(childTag));
	return (int)childList->getLength();
}

/*method to display songs*/
void XMLDomReader::displaySongs(){
	string value,name;
	cout << "Songs:" << endl;
	int j;
	for (int i = 1; i < getChildCount("songs", 0, "song"); i++){
		value = getChildValue("song", i, "song_name", 0);
		cout << "\t Song Name		" << value.c_str() << endl;
		value = getChildValue("song", i, "duration", 0);
		cout << "\t Song Duration	\t" << value.c_str() << endl;
		value = getChildValue("song", i, "song_album", 0);
		name = getChildByAttribute("album", "album_name", value.c_str());
		cout << "\t Song Album		" << name.c_str() << endl;
		cout << "\t Artists:" << endl;
		j = 0;
		while (j < getChildCount("song_artists", i-1, "song_artist"))
		{
			value = getChildValue("song_artists", i-1, "song_artist", j);
			name = getChildByAttribute("artist", "artist_name", value.c_str());
		cout << "\t \t \t \t" << name.c_str() << endl;			j++;
		}
		cout << endl;
	}
}

/*method to display artist*/
void XMLDomReader::displayArtists(){
	string value,name;
	int j;
	cout << "Artists:" << endl;
	for (int i = 1; i < getChildCount("artists",0,"artist"); i++){
		value = getChildValue("artist", i, "artist_name", 0);
		cout << "\t Artist Name		" << value.c_str() << endl;
		cout << "\t Artist Albums:	" << endl;
		j = 0;
		while (j < getChildCount("artist_albums", i-1, "artist_album")){
			value = getChildValue("artist_albums", i-1, "artist_album", j);
			name = getChildByAttribute("album", "album_name", value.c_str());
			cout << "\t \t \t \t" << name.c_str() << endl;
			j++;
		}
		cout << "\t Artist Songs:	" << endl;
		j = 0;
		while (j < getChildCount("artist_songs", i-1, "artist_song")){
			value = getChildValue("artist_songs", i-1, "artist_song", j);
			name = getChildByAttribute("song", "song_name", value.c_str());
			cout << "\t \t \t \t" << name.c_str() << endl;	
			j++;
		}
		cout << endl;
	}
}

/*method to display albums*/
void XMLDomReader::displayAlbums(){
	string value,name;
	int j;
	cout << "Albums:" << endl;
	for (int i = 1; i < getChildCount("albums", 0, "album"); i++){
		value = getChildValue("album", i, "album_name", 0);
		cout << "\t Album Name		" << value.c_str() << endl;
		cout << "\t Album Artists:	" << endl;
		j = 0;
		while (j < getChildCount("album_artists", i-1, "album_artist"))
		{
			value = getChildValue("album_artists", i-1, "album_artist", j);
			name = getChildByAttribute("artist", "artist_name", value.c_str());
			cout << "\t \t \t \t" << name.c_str() << endl;
			j++;
		}
		cout << "\t Album Songs:	" << endl;
		j = 0;
		while (j < getChildCount("album_songs", i-1, "album_song"))
		{
			value = getChildValue("album_songs", i-1, "album_song", j);
			name = getChildByAttribute("song", "song_name", value.c_str());
			cout << "\t \t \t \t" << name.c_str() << endl;
			j++;
		}
		cout << endl;
	}
}

/*method to display playlist*/
void XMLDomReader::displayPlaylists(){
	string value,name;
	int j;
	cout << "Playlists:" << endl;
	for (int i = 0; i < getChildCount("playlists", 0, "playlist"); i++){
		value = getChildValue("playlist", i, "playlist_name", 0);
		cout << "\t Playlist Name	" << value.c_str() << endl;
		j = 0;
		cout << "\t Playlist Songs:	" << endl;
		while (j < getChildCount("playlist_songs", i, "playlist_song"))
		{
			value = getChildValue("playlist_songs", i, "playlist_song", j);
			name = getChildByAttribute("song", "song_name", value.c_str());
			cout << "\t	\t \t" << name.c_str() << endl;
			j++;
		}
		cout << endl;
	}
}