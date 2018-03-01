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
	const char* attributeTag = ID;
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
	const char* attributeTag = ID;
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
	for (int i = 1; i < getChildCount(SONGS, 0, SONG); i++){
		value = getChildValue(SONG, i, SONG_NAME, 0);
		cout << "\t Song Name		" << value.c_str() << endl;
		value = getChildValue(SONG, i, DURATION, 0);
		cout << "\t Song Duration	\t" << value.c_str() << endl;
		value = getChildValue(SONG, i, SONG_ALBUM, 0);
		name = getChildByAttribute(ALBUM, ALBUM_NAME, value.c_str());
		cout << "\t Song Album		" << name.c_str() << endl;
		cout << "\t Artists:" << endl;
		j = 0;
		while (j < getChildCount(SONG_ARTISTS, i-1, SONG_ARTIST))
		{
			value = getChildValue(SONG_ARTISTS, i-1, SONG_ARTIST, j);
			name = getChildByAttribute(ARTIST, ARTIST_NAME, value.c_str());
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
	for (int i = 1; i < getChildCount(ARTISTS,0,ARTIST); i++){
		value = getChildValue(ARTIST, i, ARTIST_NAME, 0);
		cout << "\t Artist Name		" << value.c_str() << endl;
		cout << "\t Artist Albums:	" << endl;
		j = 0;
		while (j < getChildCount(ARTIST_ALBUMS, i-1, ARTIST_ALBUM)){
			value = getChildValue(ARTIST_ALBUMS, i-1, ARTIST_ALBUM, j);
			name = getChildByAttribute(ALBUM, ALBUM_NAME, value.c_str());
			cout << "\t \t \t \t" << name.c_str() << endl;
			j++;
		}
		cout << "\t Artist Songs:	" << endl;
		j = 0;
		while (j < getChildCount(ARTIST_SONGS, i-1, ARTIST_SONG)){
			value = getChildValue(ARTIST_SONGS, i-1, ARTIST_SONG, j);
			name = getChildByAttribute(SONG, SONG_NAME, value.c_str());
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
	for (int i = 1; i < getChildCount(ALBUMS, 0, ALBUM); i++){
		value = getChildValue(ALBUM, i, ALBUM_NAME, 0);
		cout << "\t Album Name		" << value.c_str() << endl;
		cout << "\t Album Artists:	" << endl;
		j = 0;
		while (j < getChildCount(ALBUM_ARTISTS, i-1, ALBUM_ARTIST))
		{
			value = getChildValue(ALBUM_ARTISTS, i-1, ALBUM_ARTIST, j);
			name = getChildByAttribute(ARTIST, ARTIST_NAME, value.c_str());
			cout << "\t \t \t \t" << name.c_str() << endl;
			j++;
		}
		cout << "\t Album Songs:	" << endl;
		j = 0;
		while (j < getChildCount(ALBUM_SONGS, i-1, ALBUM_SONG))
		{
			value = getChildValue(ALBUM_SONGS, i-1, ALBUM_SONG, j);
			name = getChildByAttribute(SONG, SONG_NAME, value.c_str());
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
	for (int i = 0; i < getChildCount(PLAYLISTS, 0, PLAYLIST); i++){
		value = getChildValue(PLAYLIST, i, PLAYLIST_NAME, 0);
		cout << "\t Playlist Name	" << value.c_str() << endl;
		j = 0;
		cout << "\t Playlist Songs:	" << endl;
		while (j < getChildCount(PLAYLIST_SONGS, i, PLAYLIST_SONG))
		{
			value = getChildValue(PLAYLIST_SONGS, i, PLAYLIST_SONG, j);
			name = getChildByAttribute(SONG, SONG_NAME, value.c_str());
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
	pImplement = DOMImplementationRegistry::getDOMImplementation((XMLCh*)LS);
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
	DomDocImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode(CORE));
	DOMNodeList* list = xmlDoc->getElementsByTagName(XMLString::transcode(SONGS));
	DOMElement* p_RootElement = dynamic_cast<DOMElement*>(list->item(0));
	p_DataElement = xmlDoc->createElement((XMLCh*)SONG);
	songId = setId(SONGS, SONG);
	songId.erase(0, 1);
	id = stoi(songId);
	id++;
	songId = "s" + to_string(id);
	wstring wSongId(songId.begin(), songId.end());
	wSong = wSongId.c_str();
	p_DataElement->setAttribute((XMLCh*)ID, wSong);
	p_RootElement->appendChild(p_DataElement);
	data = xmlDoc->createElement((XMLCh*)SONG_NAME);
	cout << "Enter the song name that you want to add" << endl;
	cin.get();
	getline(cin, name);
	wstring wName(name.begin(), name.end());
	wSong = wName.c_str();
	textNode = xmlDoc->createTextNode(wSong);
	data->appendChild(textNode);
	p_DataElement->appendChild(data);
	data = xmlDoc->createElement((XMLCh*)DURATION);
	cout << "Enter the song duration" << endl;
	getline(cin, duration);
	wstring wDuration(duration.begin(), duration.end());
	wSong = wDuration.c_str();
	textNode = xmlDoc->createTextNode(wSong);
	data->appendChild(textNode);
	p_DataElement->appendChild(data);
	data = xmlDoc->createElement((XMLCh*)SONG_ALBUM);
	cout << "Enter the album name" << endl;
	getline(cin, album);
	album = getChildByName(ALBUM, ALBUM_NAME, album.c_str());
	wstring wAlbum(album.begin(), album.end());
	wSong = wAlbum.c_str();
	textNode = xmlDoc->createTextNode(wSong);
	data->appendChild(textNode);
	p_DataElement->appendChild(data);
	data = xmlDoc->createElement((XMLCh*)SONG_ARTISTS);
	cout << "Enter the number artists contributed" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement((XMLCh*)SONG_ARTIST);
		cout << "Enter the artist name" << endl;
		cin.get();
		getline(cin, artist);
		artist = getChildByName(ARTIST, ARTIST_NAME, artist.c_str());
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
	DomDocImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode(CORE));
	DOMNodeList* list = xmlDoc->getElementsByTagName(XMLString::transcode(ARTISTS));
	DOMElement* p_RootElement = dynamic_cast<DOMElement*>(list->item(0));
	p_DataElement = xmlDoc->createElement((XMLCh*)ARTIST);
	artistId = setId(ARTISTS, ARTIST);
	artistId.erase(0, 1);
	id = stoi(artistId);
	id++;
	artistId = "a" + to_string(id);
	wstring wArtistId(artistId.begin(), artistId.end());
	wArtist = wArtistId.c_str();
	p_DataElement->setAttribute((XMLCh*)ID, wArtist);
	p_RootElement->appendChild(p_DataElement);
	data = xmlDoc->createElement((XMLCh*)ARTIST_NAME);
	cout << "Enter the artist name that you want to add" << endl;
	cin.get();
	getline(cin, name);
	wstring wName(name.begin(), name.end());
	wArtist = wName.c_str();
	textNode = xmlDoc->createTextNode(wArtist);
	data->appendChild(textNode);
	p_DataElement->appendChild(data);
	data = xmlDoc->createElement((XMLCh*)ARTIST_ALBUMS);
	cout << "Enter the number of albums artists contributed" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement((XMLCh*)ARTIST_ALBUM);
		cout << "Enter the album name" << endl;
		cin.get();
		getline(cin, album);
		album = getChildByName(ALBUM, ALBUM_NAME, album.c_str());
		wstring wAlbum(album.begin(), album.end());
		wArtist = wAlbum.c_str();
		textNode = xmlDoc->createTextNode(wArtist);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);
	data = xmlDoc->createElement((XMLCh*)ARTIST_SONGS);
	cout << "Enter the number of songs" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement((XMLCh*)ARTIST_SONG);
		cout << "Enter the song name;" << endl;
		cin.get();
		getline(cin, song);
		song = getChildByName(SONG, SONG_NAME, song.c_str());
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
	DomDocImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode(CORE));
	DOMNodeList* list = xmlDoc->getElementsByTagName(XMLString::transcode(ALBUMS));
	DOMElement* p_RootElement = dynamic_cast<DOMElement*>(list->item(0));
	p_DataElement = xmlDoc->createElement((XMLCh*)ALBUM);
	albumId = setId(ALBUMS, ALBUM);
	albumId.erase(0, 2);
	id = stoi(albumId);
	id++;
	albumId = "al" + to_string(id);
	wstring wAlbumId(albumId.begin(), albumId.end());
	wAlbum = wAlbumId.c_str();
	p_DataElement->setAttribute((XMLCh*)ID, wAlbum);
	p_RootElement->appendChild(p_DataElement);
	data = xmlDoc->createElement((XMLCh*)ALBUM_NAME);
	cout << "Enter the album name that you want to add" << endl;
	cin.get();
	getline(cin, name);
	wstring wName(name.begin(), name.end());
	wAlbum = wName.c_str();
	textNode = xmlDoc->createTextNode(wAlbum);
	data->appendChild(textNode);
	p_DataElement->appendChild(data);
	data = xmlDoc->createElement((XMLCh*)ALBUM_ARTISTS);
	cout << "Enter the number of artist contributed" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement((XMLCh*)ALBUM_ARTIST);
		cout << "Enter the artist name" << endl;
		cin.get();
		getline(cin, artist);
		artist = getChildByName(ARTIST, ARTIST_NAME, artist.c_str());
		wstring wArtist(artist.begin(), artist.end());
		wAlbum = wArtist.c_str();
		textNode = xmlDoc->createTextNode(wAlbum);
		childData->appendChild(textNode);
		data->appendChild(childData);
	}
	p_DataElement->appendChild(data);
	data = xmlDoc->createElement((XMLCh*)ALBUM_SONGS);
	cout << "Enter the number of songs" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement((XMLCh*)ALBUM_SONG);
		cout << "Enter the song name;" << endl;
		cin.get();
		getline(cin, song);
		song = getChildByName(SONG, SONG_NAME, song.c_str());
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
	DomDocImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode(CORE));
	DOMNodeList* list = xmlDoc->getElementsByTagName(XMLString::transcode(PLAYLISTS));
	DOMElement* p_RootElement = dynamic_cast<DOMElement*>(list->item(0));
	p_DataElement = xmlDoc->createElement((XMLCh*)PLAYLIST);
	playlistId = setId(PLAYLISTS, PLAYLIST);
	playlistId.erase(0, 1);
	id = stoi(playlistId);
	id++;
	playlistId = "p" + to_string(id);
	wstring wPlaylistId(playlistId.begin(), playlistId.end());
	wPlaylist = wPlaylistId.c_str();
	p_DataElement->setAttribute((XMLCh*)ID, wPlaylist);
	p_RootElement->appendChild(p_DataElement);
	data = xmlDoc->createElement((XMLCh*)PLAYLIST_NAME);
	cout << "Enter the playlist name that you want to add" << endl;
	cin.get();
	getline(cin, name);
	wstring wName(name.begin(), name.end());
	wPlaylist = wName.c_str();
	textNode = xmlDoc->createTextNode(wPlaylist);
	data->appendChild(textNode);
	p_DataElement->appendChild(data);
	data = xmlDoc->createElement((XMLCh*)PLAYLIST_SONGS);
	cout << "Enter the number of songs" << endl;
	cin >> index;
	if (cin.fail()){
		index = checkUserInput();
	}
	cin.get();
	for (int i = 0; i < index; i++){
		childData = xmlDoc->createElement((XMLCh*)PLAYLIST_SONG);
		cout << "Enter the song name;" << endl;
		getline(cin, songs);
		songs = getChildByName(SONG, SONG_NAME, songs.c_str());
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
	const char* attributeTag = ID;
	string value;
	DOMNodeList* list = xmlDoc->getElementsByTagName(XMLString::transcode(parentTag));
	for (int parentIndex = 0; parentIndex < (int)list->getLength(); parentIndex++){
		DOMElement* parent = dynamic_cast<DOMElement*>(list->item(parentIndex));
		DOMElement* child =
			dynamic_cast<DOMElement*>(parent->getElementsByTagName(XMLString::transcode(childTag))->item(0));
		if (child) {
			if (_strcmpi(childValue, XMLString::transcode(child->getTextContent())) == 0){
				value = XMLString::transcode(parent->getAttribute(XMLString::transcode(ID)));
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
	const char* attributeTag = ID;
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
	const char* attributeTag = ID;
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
