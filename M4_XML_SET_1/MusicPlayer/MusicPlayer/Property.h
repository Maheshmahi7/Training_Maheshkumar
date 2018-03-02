#define CONNECTION_DRIVER L"DRIVER={SQL Server};SERVER=IN11W-TRAINEE6\\SQLEXPRESS,49416;DATABASE=MusicPlayer;Trusted=true;"

#define XML "XML"

#define DATABASE "Database"

#define CLEAR_SCREEN "cls"

#define XML_FILE "./MusicPlayerData.xml"

#define DELETION "Deletion"

#define INSERTION "Insertion"

#define UPDATION "Updation"

#define GET_SONGS L"select * from song order by song.name"

#define GET_SONG_BY_NAME L"select song.name,song.duration,artist.name, album.name from song join song_artist on song.id = song_artist.song_id join artist on song_artist.artist_id = artist.Id  join album_song on album_song.song_id = song.Id join album on album_song.album_id = album.Id where song.name = ? order by song.name"

#define GET_ALBUMS L"select * from Album order by Album.name"

#define GET_ALBUM_SONG_BY_NAME L"select distinct Album.Name as album,Song.Name as Song from Album join Album_Song on album.id = Album_Song.album_id join Song on Song.Id = Album_Song.song_id where Album.Name = ? order by album.Name"

#define GET_ALBUM_ARTIST_BY_NAME L"Select distinct Album.Name as album,Artist.Name as Artist from Album join Album_Song on album.id = Album_Song.album_id join Song_Artist on Song_Artist.song_id = Album_Song.song_id join Artist on Artist.Id = Song_Artist.artist_id where Album.Name = ? order by album.Name"

#define GET_ARTISTS L"select * from Artist order by Artist.Name"

#define GET_ARTIST_ALBUM_BY_NAME L"select distinct Artist.Name as Artist, Album.Name as Album from Artist join Song_Artist on Song_Artist.artist_id = Artist.Id join Album_Song on Album_Song.song_id = Song_Artist.song_id join Album on Album.Id = Album_Song.album_id where Artist.Name = ? order by Artist.Name"

#define GET_ARTIST_SONG_BY_NAME L"select distinct Artist.Name as Artist,Song.Name as Song from Artist join Song_Artist on Song_Artist.artist_id = Artist.Id join Song on Song_Artist.song_id = song.Id where Artist.Name = ? order by Artist.Name"

#define GET_PLAYLISTS L"select * from Playlist order by Playlist.Name"

#define GET_PLAYLIST_BY_NAME L"select Playlist.Name,Song.Name from Song join Song_Playlist on Song.Id = Song_Playlist.song_id join Playlist on playlist.Id = Song_Playlist.playlist_id where Playlist.Name = ? order by Playlist.Name"

#define INSERT_SONG L"INSERT INTO SONG(NAME,DURATION) VALUES(?,?)"

#define INSERT_ALBUM L"INSERT INTO ALBUM(NAME) VALUES(?)"

#define INSERT_ARTIST L"INSERT INTO ARTIST(NAME,AGE,EMAIL_ID) VALUES(?,?,?)"

#define INSERT_PLAYLIST L"INSERT INTO PLAYLIST(NAME) VALUES(?)"

#define GET_SONG_ID_BY_NAME L"select song.id from Song where Song.Name = ?"

#define GET_ALBUM_ID_BY_NAME L"select album.id from Album where Album.Name= ?"

#define GET_ARTIST_ID_BY_NAME L"SELECT artist.id FROM ARTIST WHERE ARTIST.NAME= ?"

#define GET_PLAYLIST_ID_BY_NAME L"SELECT playlist.id FROM PLAYLIST WHERE PLAYLIST.NAME= ?"

#define INSERT_ALBUM_SONG L"INSERT INTO ALBUM_SONG(SONG_ID,ALBUM_ID) VALUES(?,?)"

#define INSERT_SONG_PLAYLIST L"INSERT INTO SONG_PLAYLIST(PLAYLIST_ID,SONG_ID) VALUES(?,?)"

#define INSERT_SONG_ARTIST L"INSERT INTO SONG_ARTIST(SONG_ID,ARTIST_ID) VALUES(?,?)"

#define UPDATE_SONG_NAME L"update Song set Song.Name=? where name=?"

#define UPDATE_SONG_DURATION L"update Song set Song.Duration=? where name=?"

#define UPDATE_ALBUM_NAME L"update Album set Album.Name=? where name=?"

#define UPDATE_PLAYLIST_NAME L"update Playlist set Playlist.Name=? where name=?"

#define UPDATE_ARTIST_NAME L"update Artist set Artist.Name=? where name=?"

#define UPDATE_ARTIST_EMAIL_ID L"update Artist set Artist.Email_id=? where name=?"

#define UPDATE_ARTIST_AGE L"update Artist set Artist.Age=? where name=?"

#define DELETE_SONG L"delete from song where song.name=?"

#define DELETE_ALBUM L"delete from Album where Album.name=?"

#define DELETE_ARTIST L"delete from Artist where Artist.name=?"

#define DELETE_PLAYLIST L"delete from playlist where playlist.name=?"

#define DELETE_ALBUM_SONG_SONG L"delete from Album_Song where Album_Song.song_id=?"

#define DELETE_SONG_ARTIST_SONG L"delete from Song_Artist where Song_Artist.song_id=?"

#define DELETE_SONG_PLAYLIST_SONG L"delete from Song_playlist where Song_Playlist.song_id=?"

#define DELETE_ALBUM_SONG_ALBUM L"delete from Album_Song where Album_Song.album_id=?"

#define DELETE_SONG_ARTIST_ARTIST  L"delete from Song_Artist where Song_Artist.artist_id=?"

#define DELETE_SONG_PLAYLIST_PLAYLIST L"delete from Song_playlist where Song_Playlist.playlist_id=?"
