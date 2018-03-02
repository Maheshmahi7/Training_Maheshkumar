#include "XmlParser.h"



/*parameterized constructor to assign the readed file to a local instance*/
XmlParser::XmlParser()
{	
	XMLPlatformUtils::Initialize();
	XMLDom::Instantiate();
}

XmlParser::~XmlParser()
{
	XMLPlatformUtils::Terminate();
}

/*method to get the text content from the node*/
string XmlParser::getChildValue(const char* parentTag, int parentIndex, const char* childTag, int childIndex)
{
	xercesc_3_2::DOMDocument* xmlDoc = XMLDom::getDomDoc();
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
string XmlParser::getChildByAttribute(const char* parentTag, const char* childTag , const char* attributevalue){
	xercesc_3_2::DOMDocument* xmlDoc = XMLDom::getDomDoc();
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
string XmlParser::getChildAttribute(const char* parentTag, int parentIndex, const char* childTag, int childIndex)
{
	xercesc_3_2::DOMDocument* xmlDoc = XMLDom::getDomDoc();
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
int XmlParser::getRootElementCount(const char* rootElementTag)
{
	xercesc_3_2::DOMDocument* xmlDoc = XMLDom::getDomDoc();
	DOMNodeList* list = xmlDoc->getElementsByTagName(XMLString::transcode(rootElementTag));
	return (int)list->getLength();
}

/*method to get the number of child elements*/
int XmlParser::getChildCount(const char* parentTag, int parentIndex, const char* childTag)
{
	xercesc_3_2::DOMDocument* xmlDoc = XMLDom::getDomDoc();
	XMLCh* temp = XMLString::transcode(parentTag);
	DOMNodeList* list = xmlDoc->getElementsByTagName(temp);
	XMLString::release(&temp);
	DOMElement* parent = dynamic_cast<DOMElement*>(list->item(parentIndex));
	DOMNodeList* childList = parent->getElementsByTagName(XMLString::transcode(childTag));
	return (int)childList->getLength();
}

/*method to display songs*/
void XmlParser::displaySongs(){
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
void XmlParser::displayArtists(){
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
void XmlParser::displayAlbums(){
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
void XmlParser::displayPlaylists(){
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

/*Method to write the xml from memory to local file*/
void XmlParser::addElementToFile(){
	xercesc_3_2::DOMDocument* xmlDoc = XMLDom::getDomDoc();
	DOMImplementation    *pImplement = NULL;
	DOMLSSerializer      *pSerializer = NULL;
	XMLFormatTarget      *pTarget = NULL;
	pImplement = DOMImplementationRegistry::getDOMImplementation(L"LS");
	pSerializer = ((DOMImplementationLS*)pImplement)->createLSSerializer();
	DOMConfiguration* pDomConfiguration = pSerializer->getDomConfig();
	pDomConfiguration->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
	pTarget = new LocalFileFormatTarget(XML_FILE);
	DOMLSOutput* pDomLsOutput = ((DOMImplementationLS*)pImplement)->createLSOutput();
	pDomLsOutput->setByteStream(pTarget);
	pSerializer->write(xmlDoc, pDomLsOutput);
}

/*Mehtod to add songs element to the xml file*/
string XmlParser::insertSong(){
	xercesc_3_2::DOMDocument* xmlDoc = XMLDom::getDomDoc();
	string songId, name, duration, album, artist;
	int id;
	const wchar_t* wSong;
	int index;
	DOMImplementation*    DomDocImplementation = NULL;
	DOMElement * p_DataElement = NULL;
	DOMElement * data = NULL;
	DOMText* textNode = NULL;
	DOMElement * childData = NULL;
	DomDocImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("core"));
	DOMNodeList* list = xmlDoc->getElementsByTagName(XMLString::transcode("songs"));
	DOMElement* p_RootElement = dynamic_cast<DOMElement*>(list->item(0));
	p_DataElement = xmlDoc->createElement(L"song");
	songId = setId("songs", "song");
	songId.erase(0, 1);
	id = stoi(songId);
	id++;
	songId = "s" + to_string(id);
	wstring wSongId(songId.begin(), songId.end());
	wSong = wSongId.c_str();
	p_DataElement->setAttribute(L"ID", wSong);
	p_RootElement->appendChild(p_DataElement);
	data = xmlDoc->createElement(L"song_name");
	cout << "Enter the song name that you want to add" << endl;
	cin.get();
	getline(cin, name);
	wstring wName(name.begin(), name.end());
	wSong = wName.c_str();
	textNode = xmlDoc->createTextNode(wSong);
	data->appendChild(textNode);
	p_DataElement->appendChild(data);
	data = xmlDoc->createElement(L"duration");
	cout << "Enter the song duration" << endl;
	getline(cin, duration);
	wstring wDuration(duration.begin(), duration.end());
	wSong = wDuration.c_str();
	textNode = xmlDoc->createTextNode(wSong);
	data->appendChild(textNode);
	p_DataElement->appendChild(data);
	data = xmlDoc->createElement(L"song_album");
	cout << "Enter the album name" << endl;
	getline(cin, album);
	album = getChildByName("album", "album_name", album.c_str());
	wstring wAlbum(album.begin(), album.end());
	wSong = wAlbum.c_str();
	textNode = xmlDoc->createTextNode(wSong);
	data->appendChild(textNode);
	p_DataElement->appendChild(data);
	data = xmlDoc->createElement(L"song_artists");
	cout << "Enter the number artists contributed" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"song_artist");
		cout << "Enter the artist name" << endl;
		cin.get();
		getline(cin, artist);
		artist = getChildByName("artist", "artist_name", artist.c_str());
		wstring wArtist(artist.begin(), artist.end());
		wSong = wArtist.c_str();
		textNode = xmlDoc->createTextNode(wSong);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);
	XMLDom::setDomDoc(xmlDoc);
	return "Inserted Successfully";
}

/*Method to add the artist element to the xml file*/
string XmlParser::insertArtist(){
	xercesc_3_2::DOMDocument* xmlDoc = XMLDom::getDomDoc();
	int id;
	string artistId, name, album, song;
	const wchar_t* wArtist;
	int index;
	DOMImplementation*    DomDocImplementation = NULL;
	DOMElement * p_DataElement = NULL;
	DOMElement * data = NULL;
	DOMText* textNode = NULL;
	DOMElement * childData = NULL;
	DomDocImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("core"));
	DOMNodeList* list = xmlDoc->getElementsByTagName(XMLString::transcode("artists"));
	DOMElement* p_RootElement = dynamic_cast<DOMElement*>(list->item(0));
	p_DataElement = xmlDoc->createElement(L"artist");
	artistId = setId("artists", "artist");
	artistId.erase(0, 1);
	id = stoi(artistId);
	id++;
	artistId = "a" + to_string(id);
	wstring wArtistId(artistId.begin(), artistId.end());
	wArtist = wArtistId.c_str();
	p_DataElement->setAttribute(L"ID", wArtist);
	p_RootElement->appendChild(p_DataElement);
	data = xmlDoc->createElement(L"artist_name");
	cout << "Enter the artist name that you want to add" << endl;
	cin.get();
	getline(cin, name);
	wstring wName(name.begin(), name.end());
	wArtist = wName.c_str();
	textNode = xmlDoc->createTextNode(wArtist);
	data->appendChild(textNode);
	p_DataElement->appendChild(data);
	data = xmlDoc->createElement(L"artist_albums");
	cout << "Enter the number of albums artists contributed" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"artist_album");
		cout << "Enter the album name" << endl;
		cin.get();
		getline(cin, album);
		album = getChildByName("album", "album_name", album.c_str());
		wstring wAlbum(album.begin(), album.end());
		wArtist = wAlbum.c_str();
		textNode = xmlDoc->createTextNode(wArtist);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);
	data = xmlDoc->createElement(L"artist_songs");
	cout << "Enter the number of songs" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"artist_song");
		cout << "Enter the song name;" << endl;
		cin.get();
		getline(cin, song);
		song = getChildByName("song", "song_name", song.c_str());
		wstring wSong(song.begin(), song.end());
		wArtist = wSong.c_str();
		textNode = xmlDoc->createTextNode(wArtist);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);
	XMLDom::setDomDoc(xmlDoc);
	return "Inserted Successfully";
}

/*Method to add the album element to the xml file*/
string XmlParser::insertAlbum(){
	xercesc_3_2::DOMDocument* xmlDoc = XMLDom::getDomDoc();
	int id;
	string albumId, name, song, artist;
	const wchar_t* wAlbum;
	int index;
	DOMImplementation*    DomDocImplementation = NULL;
	DOMElement * p_DataElement = NULL;
	DOMElement * data = NULL;
	DOMText* textNode = NULL;
	DOMElement * childData = NULL;
	DomDocImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("core"));
	DOMNodeList* list = xmlDoc->getElementsByTagName(XMLString::transcode("albums"));
	DOMElement* p_RootElement = dynamic_cast<DOMElement*>(list->item(0));
	p_DataElement = xmlDoc->createElement(L"album");
	albumId = setId("albums", "album");
	albumId.erase(0, 2);
	id = stoi(albumId);
	id++;
	albumId = "al" + to_string(id);
	wstring wAlbumId(albumId.begin(), albumId.end());
	wAlbum = wAlbumId.c_str();
	p_DataElement->setAttribute(L"ID", wAlbum);
	p_RootElement->appendChild(p_DataElement);
	data = xmlDoc->createElement(L"album_name");
	cout << "Enter the album name that you want to add" << endl;
	cin.get();
	getline(cin, name);
	wstring wName(name.begin(), name.end());
	wAlbum = wName.c_str();
	textNode = xmlDoc->createTextNode(wAlbum);
	data->appendChild(textNode);
	p_DataElement->appendChild(data);
	data = xmlDoc->createElement(L"album_artists");
	cout << "Enter the number of artist contributed" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"album_artist");
		cout << "Enter the artist name" << endl;
		cin.get();
		getline(cin, artist);
		artist = getChildByName("artist", "artist_name", artist.c_str());
		wstring wArtist(artist.begin(), artist.end());
		wAlbum = wArtist.c_str();
		textNode = xmlDoc->createTextNode(wAlbum);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);
	data = xmlDoc->createElement(L"album_songs");
	cout << "Enter the number of songs" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"album_song");
		cout << "Enter the song name;" << endl;
		cin.get();
		getline(cin, song);
		song = getChildByName("song", "song_name", song.c_str());
		wstring wSong(song.begin(), song.end());
		wAlbum = wSong.c_str();
		textNode = xmlDoc->createTextNode(wAlbum);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);
	XMLDom::setDomDoc(xmlDoc);
	return "Inserted Successfully";
}

/*Method to add the playlist element to the xml file*/
string XmlParser::insertPlaylist(){
	xercesc_3_2::DOMDocument* xmlDoc = XMLDom::getDomDoc();
	int id;
	string playlistId, name, songs;
	const wchar_t* wPlaylist;
	int index;
	DOMImplementation*    DomDocImplementation = NULL;
	DOMElement * p_DataElement = NULL;
	DOMElement * data = NULL;
	DOMText* textNode = NULL;
	DOMElement * childData = NULL;
	DomDocImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("core"));
	DOMNodeList* list = xmlDoc->getElementsByTagName(XMLString::transcode("playlists"));
	DOMElement* p_RootElement = dynamic_cast<DOMElement*>(list->item(0));
	p_DataElement = xmlDoc->createElement(L"playlist");
	playlistId = setId("playlists", "playlist");
	playlistId.erase(0, 1);
	id = stoi(playlistId);
	id++;
	playlistId = "p" + to_string(id);
	wstring wPlaylistId(playlistId.begin(), playlistId.end());
	wPlaylist = wPlaylistId.c_str();
	p_DataElement->setAttribute(L"ID", wPlaylist);
	p_RootElement->appendChild(p_DataElement);
	data = xmlDoc->createElement(L"playlist_name");
	cout << "Enter the playlist name that you want to add" << endl;
	cin.get();
	getline(cin, name);
	wstring wName(name.begin(), name.end());
	wPlaylist = wName.c_str();
	textNode = xmlDoc->createTextNode(wPlaylist);
	data->appendChild(textNode);
	p_DataElement->appendChild(data);
	data = xmlDoc->createElement(L"playlist_songs");
	cout << "Enter the number of songs" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	cin.get();
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement(L"playlist_song");
		cout << "Enter the song name;" << endl;
		getline(cin, songs);
		songs = getChildByName("song", "song_name", songs.c_str());
		wstring wSong(songs.begin(), songs.end());
		wPlaylist = wSong.c_str();
		textNode = xmlDoc->createTextNode(wPlaylist);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);
	XMLDom::setDomDoc(xmlDoc);
	return "Inserted Successfully";
}


/*method to validate user input of type integer*/
int XmlParser::checkUserInput() {
	int input;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "You have entered wrong input" << endl;
			cin >> input;
		}
		else if (!cin.fail()) {
			return input;
			break;
		}
	}
}

string XmlParser::getChildByName(const char* parentTag, const char* childTag, const char* childValue){
	xercesc_3_2::DOMDocument* xmlDoc = XMLDom::getDomDoc();
	const char* attributeTag = "ID";
	string value;
	DOMNodeList* list = xmlDoc->getElementsByTagName(XMLString::transcode(parentTag));
	for (int parentIndex = 0; parentIndex < (int)list->getLength(); parentIndex++){
		DOMElement* parent = dynamic_cast<DOMElement*>(list->item(parentIndex));
		DOMElement* child =
			dynamic_cast<DOMElement*>(parent->getElementsByTagName(XMLString::transcode(childTag))->item(0));
		if (child) {
			if (_strcmpi(childValue, XMLString::transcode(child->getTextContent())) == 0){
				value = XMLString::transcode(parent->getAttribute(XMLString::transcode("ID")));
				break;
			}
		}
	}
	if (value.empty()){
		value = getChildByName(parentTag, childTag, "None");
	}
	return value;
}


int XmlParser::getID(const char* parentTag, const char* childTag){
	xercesc_3_2::DOMDocument* xmlDoc = XMLDom::getDomDoc();
	const char* attributeTag = "ID";
	int parentIndex = 0;
	DOMNodeList* list = xmlDoc->getElementsByTagName(XMLString::transcode(parentTag));
	while (true){
		DOMElement* parent = dynamic_cast<DOMElement*>(list->item(parentIndex));
		char* temp2 = XMLString::transcode(parent->getAttribute(XMLString::transcode(attributeTag)));
	}
	return 0;
}


string XmlParser::setId(const char* parentTag, const char* childTag){
	xercesc_3_2::DOMDocument* xmlDoc = XMLDom::getDomDoc();
	const char* attributeTag = "ID";
	string value;
	DOMNodeList* list = xmlDoc->getElementsByTagName(XMLString::transcode(parentTag));
	DOMElement* parent = dynamic_cast<DOMElement*>(list->item(0));
	DOMNodeList* childList = parent->getElementsByTagName(XMLString::transcode(childTag));
	int length = (int)childList->getLength();
	for (int childIndex = 0; childIndex < length; childIndex++){
		DOMElement* child =
			dynamic_cast<DOMElement*>(parent->getElementsByTagName(XMLString::transcode(childTag))->item(childIndex));
		if (childIndex == 0){
			value = XMLString::transcode(child->getAttribute(XMLString::transcode(attributeTag)));
		}
		if (child) {
			char* temp = XMLString::transcode(child->getAttribute(XMLString::transcode(attributeTag)));
			int check = _strcmpi((char*)value.c_str(), temp);
			if (check < 0){
				value = temp;
			}
		}
	}
	return value;
}

/*The following methods are for future purpose only and they does do anything as of now*/
string XmlParser::updateSongName()
{
	return "s";
}
string XmlParser::updateSongDuration()
{
	return "s";
}
string XmlParser::updateAlbum()
{
	return "s";
}
string XmlParser::updatePlaylist()
{
	return "s";
}
string XmlParser::updateArtistName()
{
	return "s";
}
string XmlParser::updateArtistAge()
{
	return "s";
}
string XmlParser::updateArtistEmailId()
{
	return "s";
}

string XmlParser::deleteSong()
{
	return "s";
}
string XmlParser::deleteAlbum()
{
	return "s";
}
string XmlParser::deleteArtist()
{
	return "s";
}
string XmlParser::deletePlaylist()
{
	return "s";
}
