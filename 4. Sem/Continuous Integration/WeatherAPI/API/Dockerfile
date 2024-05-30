FROM mcr.microsoft.com/dotnet/aspnet:6.0 AS base
WORKDIR /app
EXPOSE 80

FROM mcr.microsoft.com/dotnet/sdk:6.0 AS build
WORKDIR /src
COPY ["WeatherAPI.csproj", "./"]
#Restores the dependencies and tools of the project.
RUN dotnet restore "WeatherAPI.csproj" 
COPY . .
WORKDIR "/src/."
#Builds the project and all of its dependencies.
RUN dotnet build "WeatherAPI.csproj" -c Release -o /app/build

FROM build AS publish
#Publishes the application and its dependencies to a folder for deployment to a hosting system.
RUN dotnet publish "WeatherAPI.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "WeatherAPI.dll"]