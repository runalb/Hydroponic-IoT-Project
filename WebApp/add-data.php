
<?php
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
    $v2 = $_GET["waterTemperatureFahrenhei"];
    $v3 = $_GET["dhtHumidity"];
    $v4 = $_GET["dhtTemperatureCelsius"];
    $v5 = $_GET["dhtTemperatureFahrenhei"];
    $v6 = $_GET["heatIndexCelsius"];
    $v7 = $_GET["heatIndexFahrenheit"];

    // SQL Query to add data to the DB Table
    $sql = "INSERT INTO Sensor_Data (waterTemperatureCelsius, waterTemperatureFahrenhei, dhtHumidity, dhtTemperatureCelsius, dhtTemperatureFahrenhei, heatIndexCelsius, heatIndexFahrenheit) VALUES ('$v1', '$v2', '$v3', '$v4', '$v5', '$v6', '$v7')";

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
