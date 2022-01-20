<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>View DB Data</title>
	<!-- Bootstrap CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">

</head>

<body>
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
    echo "<h2 class='text-center'>Database Connected successfully</h2>";

    $sql='SELECT * FROM sensor_data';
    $ret=mysqli_query($conn,$sql);
    
	if(mysqli_num_rows($ret)>0)
	{			          
        echo"<br>
			<table class='table'>
				<thead>
					<tr>
						<th scope='col'>Timestamp</th>
						<th scope='col'>waterTemperatureCelsius</th>
						<th scope='col'>waterTemperatureFahrenheit</th>
						<th scope='col'>dhtHumidity</th>
						<th scope='col'>dhtTemperatureCelsius</th>
						<th scope='col'>dhtTemperatureFahrenheit</th>
						<th scope='col'>heatIndexCelsius</th>
						<th scope='col'>heatIndexFahrenheit</th>
						<th scope='col'>ldrLightIntensity</th>
					</tr>
				</thead>
				<tbody>";
		while($row=mysqli_fetch_assoc($ret))
		{
			echo"<tr>
					<td>{$row['timestamp']}</td>
					<td>{$row['waterTemperatureCelsius']}</td>
					<td>{$row['waterTemperatureFahrenheit']}</td>
					<td>{$row['dhtHumidity']}</td>
					<td>{$row['dhtTemperatureCelsius']}</td>
					<td>{$row['dhtTemperatureFahrenheit']}</td>
					<td>{$row['heatIndexCelsius']}</td>
					<td>{$row['heatIndexFahrenheit']}</td>
					<td>{$row['ldrLightIntensity']}</td>
				</tr>";
		}
		echo'</tbody></table>';
                     
                  
    }
                  
	if(mysqli_num_rows($ret)==0)
        {
			echo "<h2 class='text-center'>No Data to view....</h2>";
        }
?>
                
      
</body>
</html>