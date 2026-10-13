import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.Spinner;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class TipCalculator extends Application {

    @Override
    public void start(Stage stage) {

        // Heading
        Label title = new Label("Tip Calculator");
        title.setStyle(
            "-fx-font-size: 24px; -fx-font-weight: bold;"
        );

        // Bill amount input
        Label billLabel = new Label("Bill Amount (₹):");
        TextField billField = new TextField();
        billField.setPromptText("Enter bill amount");

        // Tip percentage selection
        Label tipLabel = new Label("Tip Percentage:");
        ComboBox<Integer> tipBox = new ComboBox<>();
        tipBox.getItems().addAll(5, 10, 15, 20, 25);
        tipBox.setValue(15);
        tipBox.setMaxWidth(Double.MAX_VALUE);

        // Number of people
        Label peopleLabel = new Label("Number of People:");
        Spinner<Integer> peopleSpinner =
            new Spinner<>(1, 100, 1);
        peopleSpinner.setEditable(true);

        // Calculate button
        Button calculateButton = new Button("Calculate Tip");
        calculateButton.setMaxWidth(Double.MAX_VALUE);

        // Result labels
        Label tipResult = new Label("Tip: ₹0.00");
        Label totalResult = new Label("Total: ₹0.00");
        Label perPersonResult =
            new Label("Per Person: ₹0.00");
        Label messageLabel = new Label();

        // Layout using GridPane
        GridPane grid = new GridPane();
        grid.setHgap(12);
        grid.setVgap(15);
        grid.setPadding(new Insets(10));

        grid.add(billLabel, 0, 0);
        grid.add(billField, 1, 0);

        grid.add(tipLabel, 0, 1);
        grid.add(tipBox, 1, 1);

        grid.add(peopleLabel, 0, 2);
        grid.add(peopleSpinner, 1, 2);

        grid.add(calculateButton, 1, 3);

        // Make input controls fill their cells
        billField.setMaxWidth(Double.MAX_VALUE);

        // Event handling
        calculateButton.setOnAction(event -> {
            try {
                double bill = Double.parseDouble(
                    billField.getText().trim()
                );

                // Commit edited Spinner text
                peopleSpinner.increment(0);
                int people = peopleSpinner.getValue();
                int tipPercent = tipBox.getValue();

                if (!Double.isFinite(bill) || bill < 0) {
                    throw new IllegalArgumentException(
                        "Enter a valid non-negative bill amount."
                    );
                }

                double tip = bill * tipPercent / 100.0;
                double total = bill + tip;
                double perPerson = total / people;

                tipResult.setText(String.format(
                    "Tip: ₹%.2f", tip
                ));
                totalResult.setText(String.format(
                    "Total: ₹%.2f", total
                ));
                perPersonResult.setText(String.format(
                    "Per Person: ₹%.2f", perPerson
                ));

                messageLabel.setText("Calculation complete!");
                messageLabel.setStyle("-fx-text-fill: green;");

            } catch (NumberFormatException ex) {
                messageLabel.setText(
                    "Please enter a valid bill amount."
                );
                messageLabel.setStyle("-fx-text-fill: red;");

            } catch (IllegalArgumentException ex) {
                messageLabel.setText(ex.getMessage());
                messageLabel.setStyle("-fx-text-fill: red;");
            }
        });

        // Main vertical layout
        VBox root = new VBox(15);
        root.setPadding(new Insets(20));
        root.setAlignment(Pos.CENTER);
        root.getChildren().addAll(
            title,
            grid,
            tipResult,
            totalResult,
            perPersonResult,
            messageLabel
        );

        // Create the scene and display the window
        Scene scene = new Scene(root, 420, 430);

        stage.setTitle("JavaFX Tip Calculator");
        stage.setScene(scene);
        stage.setMinWidth(400);
        stage.setMinHeight(400);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
