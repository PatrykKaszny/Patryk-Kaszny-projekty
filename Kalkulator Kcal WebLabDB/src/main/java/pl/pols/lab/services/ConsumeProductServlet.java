package pl.pols.lab.services;

import Model.EatenProduct;
import Model.Product;
import jakarta.servlet.ServletContext;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import pl.polsl.lab.model.DataSource;
import pl.polsl.lab.model.SingletonModel;

/**
 * Servlet for handling the consumption of a product. It processes the product
 * ID and the number of grams consumed, calculates the nutritional values based
 * on the given weight, and updates the total consumption in the model.
 * 
 * @version 1.1.0
 * @since 1.0
 * @author Patryk Kaszny
 */
@WebServlet("/consumeProduct")
public class ConsumeProductServlet extends HttpServlet {

    /**
     * Handles the HTTP POST request to consume a product. It calculates the nutritional
     * values based on the product's weight (grams consumed) and updates the consumed product list.
     * It also returns a summary of the nutritional information for the consumed product.
     * 
     * @param request the HTTP request object containing the product ID and grams consumed
     * @param response the HTTP response object to send back the result
     * @throws ServletException if a servlet-specific error occurs during processing the request
     * @throws IOException if an I/O error occurs while generating the response
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        try {
            ServletContext context = request.getServletContext();
            DataSource dataSource = (DataSource) context.getAttribute("DataSource");

            // Retrieve the product ID and grams from the request parameters
            int productId = Integer.parseInt(request.getParameter("id"));
            int grams = Integer.parseInt(request.getParameter("grams"));

            // Retrieve the product from the list using the provided ID
            Product product = SingletonModel.getInstance().getAllProductList().get(productId);

            // Check if the product exists
            if (product == null) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Product does not exist");
                return;
            }

            // Calculate nutritional values based on the grams consumed
            double calories = (product.getKcal() / 100.0) * grams;
            double protein = (product.getProtein() / 100.0) * grams;
            double carbs = (product.getCarb() / 100.0) * grams;
            double fat = (product.getFat() / 100.0) * grams;

            // Add the consumed product to the model
            EatenProduct consumedProduct = new EatenProduct(product, (int) grams);
            dataSource.updateEatenProduct(consumedProduct);
            SingletonModel.getInstance().addEatenProducts(
                product.getName(), 
                (int) grams, 
                (int) calories, 
                (int) protein, 
                (int) carbs, 
                (int) fat
            );

            // Send a summary of the consumed product to the response
            response.setContentType("text/plain;charset=UTF-8");
            PrintWriter out = response.getWriter();
            out.println("Consumed: " + grams + "g " + product.getName());
            out.println("Calories: " + calories + ", Protein: " + protein + "g, Carbs: " + carbs + "g, Fat: " + fat + "g");

        } catch (Exception e) {
            // Handle invalid input or other errors
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid input data");
        }
    }
}
