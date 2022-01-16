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
						<th scope='col'>value1</th>
						<th scope='col'>value2</th>
						<th scope='col'>value3</th>
						<th scope='col'>value4</th>
						<th scope='col'>value5</th>
					</tr>
				</thead>
				<tbody>";
		while($row=mysqli_fetch_assoc($ret))
		{
			echo"<tr>
					<td>{$row['timestamp']}</td>
					<td>{$row['value1']}</td>
					<td>{$row['value2']}</td>
					<td>{$row['value3']}</td>
					<td>{$row['value4']}</td>
					<td>{$row['value5']}</td>
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