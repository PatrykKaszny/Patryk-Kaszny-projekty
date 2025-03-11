package pl.pols.lab.services;

import Model.Product;
import jakarta.servlet.ServletContext;
import jakarta.servlet.http.HttpServlet;
import pl.polsl.lab.model.DataSource;
import pl.polsl.lab.model.DatabaseSource;

/**
 * Servlet to initialize the data source for the application. It ensures that
 * the appropriate data source is set up in the servlet context when the servlet
 * is initialized.
 * 
 * @version 1.0.0
 * @since 1.0
 * @author Patryk Kaszny
 */
public class InitializationServlet extends HttpServlet { 

    /**
     * Initializes the servlet by setting the data source in the servlet context.
     * If no data source is found, it sets a new instance of {@link DatabaseSource} as the data source.
     * This method is called when the servlet is loaded into the servlet container.
     */
    @Override
    public void init() {
        
        // Retrieve the servlet context
        var context = getServletContext();  
        
        // Get the DataSource from the context
        DataSource dataSource = (DataSource) context.getAttribute("DataSource");
        
        // If no DataSource is found, set a new DatabaseSource instance
        if (dataSource == null) {
            // Uncomment the line below if you want to use a different data source (e.g., People)
            // context.setAttribute("DataSource", new People());
            context.setAttribute("DataSource", new DatabaseSource());
        }
    }   
}
