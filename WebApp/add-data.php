
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
    $v1 = $_GET["v1"];
    $v2 = $_GET["v2"];
    $v3 = $_GET["v3"];
    $v4 = $_GET["v4"];
    $v5 = $_GET["v5"];

    // SQL Query to add data to the DB Table
    $sql = "INSERT INTO Sensor_Data (value1, value2, value3, value4, value5) VALUES ('$v1', '$v2', '$v3', '$v4', '$v5')";

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
