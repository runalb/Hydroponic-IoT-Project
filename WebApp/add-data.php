<?php
    // v3 - Final

    // Database Credentials
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "hydroponic_sensor_db";

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);

    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    } 
    //echo "Connected successfully";

    // Get Data from HTTP request
    $v1 = $_GET["waterTemperatureCelsius"];
    $v2 = $_GET["waterTemperatureFahrenheit"];
    $v3 = $_GET["dhtHumidity"];
    $v4 = $_GET["dhtTemperatureCelsius"];
    $v5 = $_GET["dhtTemperatureFahrenheit"];
    $v6 = $_GET["heatIndexCelsius"];
    $v7 = $_GET["heatIndexFahrenheit"];
    $v8 = $_GET["ldrLightIntensity"];
    $v9 = $_GET["phValue"];


    

    // SQL Query to add data to the DB Table
    $sql = "INSERT INTO Sensor_Data (waterTemperatureCelsius, waterTemperatureFahrenheit, dhtHumidity, dhtTemperatureCelsius, dhtTemperatureFahrenheit, heatIndexCelsius, heatIndexFahrenheit, ldrLightIntensity, phValue) VALUES ('$v1', '$v2', '$v3', '$v4', '$v5', '$v6', '$v7', '$v8', '$v9')";

    // Add data to DB
    if ($conn->query($sql) === TRUE) {
        
        echo "SUCCESS : Added to Database";
        
        } else {
            // Error Info
            echo "ERROR :". $conn->error;
        }

        // Close DB connetion
        $conn->close();
?>
