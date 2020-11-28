docker build --tag kacassonnebuild:1.0 .
docker run -v /media/thomas/Data/Programmieren/Spiele/Kacassonne:/data kacassonnebuild:1.0 /build.sh