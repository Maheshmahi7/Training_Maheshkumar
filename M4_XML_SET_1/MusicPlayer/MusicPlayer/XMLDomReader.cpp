#include "XMLDomReader.h"




XMLDomReader::XMLDomReader(DOMDocument* doc)
{	
	xmlDoc = doc;
}

XMLDomReader::~XMLDomReader()
{
}

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
string XMLDomReader::getChildByAttribute(const char* parentTag, const char* childTag , const char* attributevalue){
	const char* attributeTag = "ID";
	int parentIndex = 0;
	string value;
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
				value = "";
			}
			XMLString::release(&temp2);
		}
		else {
			parentIndex++;
		}
	}
	return value;
}

string XMLDomReader::getChildAttribute(const char* parentTag, int parentIndex, const char* childTag, int childIndex,
	const char* attributeTag)
{
	XMLCh* temp = XMLString::transcode(parentTag);
	DOMNodeList* list = xmlDoc->getElementsByTagName(temp);
	XMLString::release(&temp);

	DOMElement* parent = dynamic_cast<DOMElement*>(list->item(parentIndex));
	DOMElement* child =
		dynamic_cast<DOMElement*>(parent->getElementsByTagName(XMLString::transcode(childTag))->item(childIndex));
	string value;
	if (child) {
		temp = XMLString::transcode(attributeTag);
		char* temp2 = XMLString::transcode(child->getAttribute(temp));
		value = temp2;
		XMLString::release(&temp2);
	}
	else {
		value = "";
	}
	return value;
}

int XMLDomReader::getRootElementCount(const char* rootElementTag)
{
	DOMNodeList* list = xmlDoc->getElementsByTagName(XMLString::transcode(rootElementTag));
	return (int)list->getLength();
}

int XMLDomReader::getChildCount(const char* parentTag, int parentIndex, const char* childTag)
{
	XMLCh* temp = XMLString::transcode(parentTag);
	DOMNodeList* list = xmlDoc->getElementsByTagName(temp);
	XMLString::release(&temp);

	DOMElement* parent = dynamic_cast<DOMElement*>(list->item(parentIndex));
	DOMNodeList* childList = parent->getElementsByTagName(XMLString::transcode(childTag));
	return (int)childList->getLength();
}

void XMLDomReader::displaySongs(){
	string value,name;
	cout << "Songs:" << endl;
	int j;
	for (int i = 0; i < getChildCount("songs", 0, "song"); i++){
		value = getChildValue("song", i, "song_name", 0);
		cout << "\t Song Name		" << value.c_str() << endl;
		value = getChildValue("song", i, "duration", 0);
		cout << "\t Song Duration	\t" << value.c_str() << endl;
		value = getChildValue("song", i, "song_album", 0);
		name = getChildByAttribute("album", "album_name", value.c_str());
		cout << "\t Song Album		" << name.c_str() << endl;
		cout << "\t Artists:" << endl;
		j = 0;
		while (j < getChildCount("song_artists", i, "song_artist"))
		{
			value = getChildValue("song_artists", i, "song_artist", j);
			name = getChildByAttribute("artist", "artist_name", value.c_str());
		cout << "\t \t \t \t" << name.c_str() << endl;			j++;
		}
		cout << endl;
	}
}

void XMLDomReader::displayArtists(){
	string value,name;
	int j;
	cout << "Artists:" << endl;
	for (int i = 0; i < getChildCount("artists",0,"artist"); i++){
		value = getChildValue("artist", i, "artist_name", 0);
		cout << "\t Artist Name		" << value.c_str() << endl;
		cout << "\t Artist Albums:	" << endl;
		j = 0;
		while (j < getChildCount("artist_albums", i, "artist_album")){
			value = getChildValue("artist_albums", i, "artist_album", j);
			name = getChildByAttribute("album", "album_name", value.c_str());
			cout << "\t \t \t \t" << name.c_str() << endl;
			j++;
		}
		cout << "\t Artist Songs:	" << endl;
		j = 0;
		while (j < getChildCount("artist_songs", i, "artist_song")){
			value = getChildValue("artist_songs", i, "artist_song", j);
			name = getChildByAttribute("song", "song_name", value.c_str());
			cout << "\t \t \t \t" << name.c_str() << endl;	
			j++;
		}
		cout << endl;
	}
}

void XMLDomReader::displayAlbums(){
	string value,name;
	int j;
	cout << "Albums:" << endl;
	for (int i = 0; i < getChildCount("albums", 0, "album"); i++){
		value = getChildValue("album", i, "album_name", 0);
		cout << "\t Album Name		" << value.c_str() << endl;
		cout << "\t Album Artists:	" << endl;
		j = 0;
		while (j < getChildCount("album_artists", i, "album_artist"))
		{
			value = getChildValue("album_artists", i, "album_artist", j);
			name = getChildByAttribute("artist", "artist_name", value.c_str());
			cout << "\t \t \t \t" << name.c_str() << endl;
			j++;
		}
		cout << "\t Album Songs:	" << endl;
		j = 0;
		while (j < getChildCount("album_songs", i, "album_song"))
		{
			value = getChildValue("album_songs", i, "album_song", j);
			name = getChildByAttribute("song", "song_name", value.c_str());
			cout << "\t \t \t \t" << name.c_str() << endl;
			j++;
		}
		cout << endl;
	}
}


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